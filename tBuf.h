/*
  Implements a buffer with fixed time steps and number of elements.
  This allows logging over fixed periods of time, i.e the last 24 hrs 
  with resolution of 1 hr
  Created: 19 Apr, 2020, zyxx
  Last Update: 
*/
#ifndef tBuf_h
#define tBuf_h

#define DEBUG 1

#include <time.h>

class tBuf
{
 public:
  // constructor
  // milUpdate: length of one buffer element in millis
  // nBuf: number of buffer elements
  // int agType: Aggregation method. 0 - average, 1 - sum
  tBuf(int secUpdate, int nBuf, int agType);
  tBuf();

  // push one Element into current buffer position
  void pushEle(float element);
  
  // pop nIndex Element from buffer, 0 is the current element,
  // (nBuf - 1) is the oldest element
  float popEle(int nIndex);
  // get number of elements stored at nIndex buffer position
  int  numEle(int nIndex);
  // get current position index in buffer
  int getIndex();
  

  // get length of buffer
  int getNBuf();
  // get length of update interval in seconds
  int getUpdTime();
  
  
 private:
  time_t _currTime;  // current time
  time_t _edgeTime;  // time when last buffer starts
  int     _updTime;  // update interval in seconds
  
    
  int _nBuf, _agType;

  float* _valBuf = nullptr;  // pointer to buffer array holding element sum
  int*   _numBuf = nullptr;  // pointer to buffer array holding number of elements
  int    _indBuf = 0;        // index into current element of ring buffer
  int    _debug  = DEBUG;    // Debug Level

  void _updateIndBuf();
};

#endif
