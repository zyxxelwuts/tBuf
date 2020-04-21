/*
  Implements a buffer with fixed time steps and number of elements.
  This allows logging over fixed periods of time, i.e the last 24 hrs 
  with resolution of 1 hr
  Created: 19 Apr, 2020, zyxx
  Last Update: 
*/

#include <tBuf.h>
#include <time.h>
#include <stdio.h>

// constructors
tBuf::tBuf(int secUpdate, int nBuf, int agType)
{
  _updTime = secUpdate;
  _nBuf = nBuf;
  _agType = agType;

  _valBuf = new float[nBuf];
  _numBuf = new int[nBuf];
  for (int i = 0; i<nBuf; i++) {
    _valBuf[i] = 0.0;
    _numBuf[i] = 0;
  }

  // initialize whe starts to count
  _edgeTime = time(NULL);
  
}
tBuf::tBuf(){};

void tBuf::_updateIndBuf()
{
  if (_debug > 0 )
    fprintf(stderr, "Entering _updateIndBuf()\n");
  // get current time
  _currTime = time(NULL);

  if (_debug > 0 ) {
    fprintf(stderr, "%ld, %ld, %ld\n",
	   (long) _currTime, (long) _edgeTime, (long) _updTime);
  }
  // i is the increase in buffer index
  int i = (int) difftime(_currTime,_edgeTime)/_updTime;
  if ( _debug > 0 ) {
    fprintf(stderr, "New Buffer Index %d\n",i);
  }
  // forward edge millis as well, hope this helps for wrapaoround (after 50 days :-))
  _edgeTime = _edgeTime + _updTime * i;
  _indBuf += i % _nBuf;
}



// push one Element into current buffer position
void tBuf::pushEle(float element)
{

  // determine the correct buffer position
  _updateIndBuf();

  // Add value to buffer
  _valBuf[_indBuf] += element;
  _numBuf[_indBuf]++;

}

float tBuf::popEle(int nIndex){
  _updateIndBuf();
  int i = (nIndex + _indBuf) % _nBuf;
  
  switch ( _agType )
    {
    case 0:
      return _valBuf[i]/ (float) _numBuf[i];
      break;
    case 1:
      return _valBuf[i];
      break;
    default:
      return _valBuf[i]/ (float) _numBuf[i];
      break;      
    }
    
};

// get number of elements from nIndex buffer position
int  tBuf::numEle(int nIndex){
  _updateIndBuf();
  int i = (nIndex + _indBuf) % _nBuf;
  return _numBuf[i];
};

// get length of buffer
int tBuf::getNBuf(){return _nBuf;};
// get length of update interval
int tBuf::getUpdTime(){return (int)  _updTime / CLOCKS_PER_SEC ;};
// get current Index
int tBuf::getIndex()
{
  _updateIndBuf();
  return _indBuf;
}
