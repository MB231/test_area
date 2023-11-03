#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
 
std::condition_variable cv;
    /* class used with a mutex to synchronize between threads
     * locks mutex and uses notify_one or notify_all to synchronize
     * WORKS ONLY WITH std::unique_lock<std::mutex> to allow macimal efficency on some platfolms
     *      use  std::condition_variable_any provides a condition variable that works with any 
     *      BasicLockable object, such as std::shared_lock.
     * Condition variables permit concurrent invocation of the wait, wait_for, wait_until, notify_one
     * and notify_all member functions.
     *
     * The class std::condition_variable is a StandardLayoutType. It is not CopyConstructible, 
     * MoveConstructible, CopyAssignable, or MoveAssignable.
     */
std::mutex cv_m; // This mutex is used for three purposes:
                 // 1) to synchronize accesses to i
                 // 2) to synchronize accesses to std::cerr
                 // 3) for the condition variable cv
int i = 0;
 
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
        /* Any thread that intends to wait on std::condition_variable has to:
         *      1.) acquire a std::unique_lock<std::mutex>, on the same mutex as used to protect the shared variable
         *      2.) either
         *          a.)check the condition, in case it was already updated and notified
         *          b.)execute wait, wait_for, or wait_until. The wait operations atomically release the mutex
         *              and suspend the execution of the thread.
         *          c.)When the condition variable is notified, a timeout expires, or a spurious wakeup occurs,
         *              the thread is awakened, and the mutex is atomically reacquired. The thread should then
         *              check the condition and resume waiting if the wake up was spurious.
         *       OR
         *       1.) use the predicated overload of wait, wait_for, and wait_until, which takes care of the three steps above
         * USE: lock,try_lock,try_lock_for,try_lock_until, or condition variable functions to lock and unlock or cond var to 
         *      unlock the unique_lock
         *      Ex code: see end of file for larger example with lock() and unlock() functions
         *      // don't actually take the locks yet
         *      std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
         *      std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
         *
         *      lock both unique_locks without deadlock
         *      std::lock(lock1, lock2); //use to lock mutliple objects at once
         */
    std::cerr << "Waiting... \n";

    //wait_until and wait_for also are alternatives see bottom of file
    cv.wait(lk, []{return i == 1;});
        /* void wait( std::unique_lock<std::mutex>& lock, Predicate pred );
         * equivalent to:
         * while (!pred()) {
         * wait(lock);
         * }
         * lock is an object locked by current thread
         * pred returns false if wait is to be continued and should by "bool pred();"
         * prototype function.
         * wait causes current thread to block until condition variable is notified OR
         * spurious wakeup occurs optionally looping until some predicate is satisfied.
         */
    std::cerr << "...finished waiting. i == 1\n";
}
 
void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
            /* mutex wrapper to make a RAII(resource acquisition is initialization, binds life cycle
             * of a resouce to the lifetime of an object and requires it be allocated before use) style
             * interface ofr owning a mutex for the duration of a scoped block.
             */
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();
        /* Notify all unblocks all threads currently waithing for *this. Notifying
         * thread does not need to hold the lock on the same mutex as the one held by
         * the waiting threads and should not since it would be blocked immmediately 
         * waiting again for the notifying thread to release the lock.
         */
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}
 
int main()
{
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
        /*
         * thread starts off thread can pass in argument like
         * std::thread t1(waits,1), t2(eaits,2), t3(other);
         * tX is the thread objext
         * waits or other is a function with "void waits(int idx)" and "void other()" 
         * prototypes
         * 1 and 2 are the arguments passed and is a good idea that it's the thread id
         * can be moved not copied and has swap function
         * Notable Functions
         * std::thread::id get_id() const noexcept
         *  returns id of thread associated with *this
         *  USE:
         *      std::thread t1(foo);
         *      std::thread::id t1_id = t1.get_id();
         * bool joinable() const noexcept;
         *  checks if it's active thread of execution returning true if get_id() != std::thread::id()
         *  active execution == finished executing code but not joined yet
         *  before starting a thread joinable is false
         *  after starting a thread joinable is true
         *  after joining a thread joinable is false
         *  after detach a thread joinable is false
         * void join()
         *  blocks current thread until the thread joining finishes execution(identified by *this)
         *  joinable must false after join is done
         * void detach()
         *  seperates the thread of execution from thread object and freeing resources independently
         *  joinable will false after detach
         */
    t1.join(); 
    t2.join(); 
    t3.join();
    t4.join();
}
/* should output:
 * Waiting...
 * Waiting...
 * Waiting...
 * Notifying...
 * Notifying again...
 * ...finished waiting. i == 1
 * ...finished waiting. i == 1
 * ...finished waiting. i == 1
*/




/* wait_for
 * template< class Rep, class Period, class Predicate >
 * bool wait_for( std::unique_lock<std::mutex>& lock,
 *          const std::chrono::duration<Rep, Period>& rel_time,
 *          Predicate pred);
 * HAS other version that returns cv_status which is an enum that tells timeout of cond var and
 * that one doesnt have predicate function as 3rd argument
 * Lock, is unique_lock type if cond var is used, but can be any lockable type for other
 * rel_time, is an std::chrono::duration type as timeout to wait.  NOTE must not overflow when 
 *      added to std::chrono::steady_clock::now()
 * pred, is something that returns false if wait is to continue with prototype bool pred()
 * USE:
 * void waits(int idx) {
 *      std::unique_lock<std::mutex> lk(cv_m);
 *      if(cv.wait_for(lk, idx*100ms, []{return i == 1;})) 
 *      std::cerr << "Thread " << idx << " finished waiting. i == " << i << '\n';
 *      else
 *      std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
 * }
 */


/*wait_until
 * template< class Clock, class Duration, class Pred >
 * bool wait_until( std::unique_lock<std::mutex>& lock,
 *                  const std::chrono::time_point<Clock, Duration>& timeout_time,
 *                  Pred pred );
 * Equivalent to:
 *      while (!pred()) {
 *          if (wait_until(lock, timeout_time) == std::cv_status::timeout) {
 *          return pred();
 *          }
 *       }
 *       return true;
 * Lock, is unique_lock type if cond var is used, but can be any lockable type for other
 * timeout_time, is an object of std::chrono::time_point representing time to stop waiting
 * pred, is something that returns false if wait is to continue with prototype bool pred()
 *
 * USE:
 * void waits(int idx) {
 *      std::unique_lock<std::mutex> lk(cv_m);
 *      auto now = std::chrono::system_clock::now();
 *      if(cv.wait_until(lk, now + idx*100ms, [](){return i == 1;}))
 *      std::cerr << "Thread " << idx << " finished waiting. i == " << i << '\n';
 *      else
 *      std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
 * }
 */


/* unique_lock example with only method functions for lock and unlock
 * #include <mutex>
 * #include <thread>
 * #include <iostream>
 * #include <vector>
 * #include <chrono>
 *
 * int main() {
 *      int counter = 0;
 *      std::mutex counter_mutex;
 *      std::vector<std::thread> threads;
 *
 *      auto worker_task = [&](int id) {
 *          std::unique_lock<std::mutex> lock(counter_mutex);
 *          ++counter;
 *          std::cout << id << ", initial counter: " << counter << '\n';
 *          lock.unlock();
 *
 *          don't hold the lock while we simulate an expensive operation
 *          std::this_thread::sleep_for(std::chrono::seconds(1));
 *
 *          lock.lock();
 *          ++counter;
 *          std::cout << id << ", final counter: " << counter << '\n';
 *          };
 *       for (int i = 0; i < 10; ++i) threads.emplace_back(worker_task, i);
 *       for (auto &thread : threads) thread.join();
 * }
 */

































