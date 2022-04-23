// A simple timer interface. based on the example timer interface written by Ken Wilder (http://sites.google.com/site/jivsoft/Home/timer).
// Modified by Vladeta Stojanovic (0602920@live.abertay.ac.uk)

#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iomanip>

class timer
{
 public:

  timer() : running(false), start_clock(0), start_time(0), acc_time(0) { }

  double elapsed_time();
  void start(const char* msg = 0);
  void SetToZero();
  void restart(const char* msg = 0);
  void stop(const char* msg = 0);
  float check();

  //Added by Vlad
  void wait(int waitTime);

private:
  bool running;
  clock_t start_clock;
  time_t start_time;
  double acc_time;

}; // class timer


inline double timer::elapsed_time()
{
  time_t acc_sec = time(0) - start_time;
  if (acc_sec < 3600)
    return (clock() - start_clock) / (1.0 * CLOCKS_PER_SEC);
  else
    return (1.0 * acc_sec);
}

inline void timer::start(const char* msg)
{
  // Return immediately if the timer is already running
  if (running) return;

  // Set timer status to running and set the start time
  running = true;
  start_clock = clock();
  start_time = time(0);

} 

inline void timer::restart(const char* msg)
{
  // Set timer status to running, reset accumulated time, and set start time
  running = true;
  acc_time = 0;
  start_clock = clock();
  start_time = time(0);

} 

inline void timer::SetToZero()
{
	acc_time = 0;
}

// Stop the timer 

inline void timer::stop(const char* msg)
{
  // Compute accumulated running time and set timer status to not running
  if (running) acc_time += elapsed_time();
  running = false;

} 

inline float timer::check()
{
   return (float) acc_time + (running ? elapsed_time() : 0);
} 


//Added by Vlad
inline void timer::wait(int waitTime)
{
	for(int i = waitTime; i > 0; --i)
	{
		//do nothing
	}
}

extern timer* gTimer;

#endif 

