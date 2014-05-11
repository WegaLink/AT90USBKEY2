//////////////////////////////////////////////////////////////////////////////
//
// CmTypes.h - Declaration of basic type and diagnostics classes
//
//////////////////////////////////////////////////////////////////////////////
//
// author: 	   Eckhard Kantz
// website:    http://wegalink.eu
//
//////////////////////////////////////////////////////////////////////////////
/* 
This is FREE software  

Permission is hereby granted, free of charge,  to any person obtaining  a copy 
of this software and associated documentation files (the "Software"),  to deal 
in the Software without restriction, including without limitation  the  rights 
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell 
copies  of  the  Software,   and  to  permit  persons  to  whom  the  Software 
is furnished to do so, subject to the following conditions: 

There are no conditions imposed on the use of this software. 

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT  WARRANTY  OF ANY KIND,  EXPRESS OR 
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE  WARRANTIES OF MERCHANTABILITY, 
FITNESS  FOR  A  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER 
LIABILITY,  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN  THE 
SOFTWARE. 
*/

#ifndef CmTypesH
#define CmTypesH

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>
#include <sys/timeb.h>
#include <math.h>
#include <share.h>

// Include all return values that apply for Cm namespace
#include "CmReturn.h"


#ifndef WIN32
//------------Unix------------
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/param.h>
#define MKDIR(path,mask) mkdir(path,mask)
#define GETCWD(buf,len)  getcwd(buf,len)
#define OPEN(buf,mode,access) open(buf,mode,access)
//------------Unix: 32-bit/64-bit compatibility------------
typedef __int64_t     int64;
typedef __uint64_t    uint64;
typedef __int32_t     int32;
typedef __uint32_t    uint32;
typedef __int16_t     int16;
typedef __uint16_t    uint16;
typedef char          int8;
typedef unsigned char uint8;
#define abs64	llabs
#else

//============================ Windows =========================================
//#include <windows.h>
#include <io.h>
#include <direct.h>
#include <winsock2.h>

//---Common MVC and BVC
#define MAXPATHLEN 1024
#define GETCWD(buf,len) GetCurrentDirectory(len,buf)

//--------- Borland C++ 6.0 -----------------
#ifdef __BORLANDC__

#define MKDIR(path,mask) mkdir(path)
#define OPEN(buf,mode,access) _open(buf,mode)
#define WRITE(fp,data,length) _write(fp,data,length)

#define open open
#define ftime ftime
#define max(a, b)  (((a) > (b)) ? (a) : (b))  
#define min(a, b)  (((a) < (b)) ? (a) : (b))

// 2007-01-21/EKantz: problem with non-existing abs64/llabs in BORLANDC
#define abs64 llabs

//--------- Microsoft Visual C++ -------------
#else

#define open  _open
#define read	_read
#define close _close
#define fstat _fstat
#define stat  _stat
#define ftime _ftime
#define abs64	_abs64
#define chdir _chdir

#ifdef O_RDONLY
  #undef O_RDONLY
#endif
#define O_RDONLY   _O_RDONLY
#define timeb	   _timeb
#define MKDIR(path,mask) _mkdir(path)
#define GETCWD(buf,len) GetCurrentDirectory(len,buf)
#define OPEN(buf,mode,access) _open(buf,mode)
#define WRITE(fp,data,length) _write(fp,data,length)

#define MAXPATHLEN 1024
// Define all unix access masks
#define __S_IREAD       0400    /* Read by owner.  */
#define __S_IWRITE      0200    /* Write by owner.  */
#define __S_IEXEC       0100    /* Execute by owner.  */
#if defined __USE_MISC && defined __USE_BSD
# define S_IREAD        S_IRUSR
# define S_IWRITE       S_IWUSR
# define S_IEXEC        S_IXUSR
#endif
#define S_IRGRP (S_IRUSR >> 3)  /* Read by group.  */
#define S_IWGRP (S_IWUSR >> 3)  /* Write by group.  */
#define S_IXGRP (S_IXUSR >> 3)  /* Execute by group.  */
/* Read, write, and execute by group.  */
#define S_IRWXG (S_IRWXU >> 3)
#define S_IROTH (S_IRGRP >> 3)  /* Read by others.  */
#define S_IWOTH (S_IWGRP >> 3)  /* Write by others.  */
#define S_IXOTH (S_IXGRP >> 3)  /* Execute by others.  */
/* Read, write, and execute by others.  */
#define S_IRWXO (S_IRWXG >> 3)

#endif //#ifdef __BORLANDC__

//------------Win: 32-bit/64-bit compatibility------------
typedef __int64            int64;
typedef unsigned __int64   uint64;
typedef __int32            int32;
typedef unsigned int       uint32;
typedef __int16            int16;
typedef unsigned __int16   uint16;
typedef char               int8;
typedef unsigned char      uint8;

#endif // #ifndef WIN32


//----------MSVS: Avoid safe functions warnings------------
#ifdef MSVS
  #define STRCPY(a,b,c)  strcpy_s(a,b,c)
  #define STRNCPY(a,b,c,d)  strncpy_s(a,b,c,d)
  #define SPRINTF3(a,b,c) sprintf_s(a,b,c)
  #define SPRINTF4(a,b,c,d) sprintf_s(a,b,c,d)
  #define SPRINTF5(a,b,c,d,e) sprintf_s(a,b,c,d,e)
  #define SPRINTF6(a,b,c,d,e,f) sprintf_s(a,b,c,d,e,f)
  #define SPRINTF7(a,b,c,d,e,f,g) sprintf_s(a,b,c,d,e,f,g)
  #define SPRINTF8(a,b,c,d,e,f,g,h) sprintf_s(a,b,c,d,e,f,g,h)
  #define SPRINTF9(a,b,c,d,e,f,g,h,i) sprintf_s(a,b,c,d,e,f,g,h,i)
#else
  #define STRCPY(a,b,c)  strcpy(a,c)
  #define STRNCPY(a,b,c,d)  strncpy(a,c,d)
  #define SPRINTF3(a,b,c) sprintf(a,c)
  #define SPRINTF4(a,b,c,d) sprintf(a,c,d)
  #define SPRINTF5(a,b,c,d,e) sprintf(a,c,d,e)
  #define SPRINTF6(a,b,c,d,e,f) sprintf(a,c,d,e,f)
  #define SPRINTF7(a,b,c,d,e,f,g) sprintf(a,c,d,e,f,g)
  #define SPRINTF8(a,b,c,d,e,f,g,h) sprintf(a,c,d,e,f,g,h)
  #define SPRINTF9(a,b,c,d,e,f,g,h,i) sprintf(a,c,d,e,f,g,h,i)
#endif  // #ifdef MSVS


//--------------------DEV C++ compatibility----------------
#ifdef gcc
  #define MIN_INT64         0x8000000000000000ull
  #define MAX_INT64         0x7FFFFFFFFFFFFFFFull
  #define MAX_UINT64        0xFFFFFFFFFFFFFFFFull
#else
  #define MIN_INT64         0x8000000000000000
  #define MAX_INT64         0x7FFFFFFFFFFFFFFF
  #define MAX_UINT64        0xFFFFFFFFFFFFFFFF
#endif // #ifdef gcc


#define MIN_INT16           0x8000
#define MAX_INT16           0x7FFF
#define MAX_UINT16	        0xFFFF

#define MIN_INT32           0x80000000
#define MAX_INT32           0x7FFFFFFF
#define MAX_UINT32	        0xFFFFFFFF

#define LO64(x)		        (uint32)(x&0xFFFFFFFF)
#define HI64(x)		        (uint32)(x>>32)


namespace Cosmos
{

//Collection of characters that function as delimiters in path strings
#define CM_PATH_DELIMITERS             "\\/"

class CmLString;
class CmMString;

//CmString provides convenient functions for string handling
class CmString
{
protected:
	int8*  pText;	//char field
	uint32 uLength;	//string length

public:
	//Parse current string and return a list of substrings accordingly to patterns
	//defined by a regular expression. The following expressions are recognized so far:
	// characters:
	//     . - any character
	//    \s - space character (\t,\r,\n)
	//    \d - digit character 0..9
	//    \w - word character _a..zA..Z
	//    others - will be treated as the particular character, e.g. a is a and ! is !
    // modifiers:
	//	   * - any number of occurrencies from 0..MAX_UNSIGNED_INT
	//     + - at least one up to any number 1..MAX_UNSIGNED_INT
	//     ? - non-mandatory occurrence (zero or one times)
	//    () - enclose components to be extracted
	uint32 Match(CmLString**, int8 const*);

	//String assignment, compare and processing functions
	void operator=(const CmString&);
	void operator=(const int8*);
	void operator=(const int32);
	void operator=(const uint32);
	void operator=(const uint64);
  //CmString& operator+(const CmString);
  //CmString& operator+(const int8*);
	void operator+=(CmString&);
	void operator+=(const int8*);
	void operator+=(int32);
	void operator+=(uint32);
	void operator+=(uint64);
	bool operator==(const CmString&);
	bool operator==(int8*);
	bool operator!=(const CmString&);
	bool operator!=(int8*);
	int compareHeader(const int8*);

	//Several access functions to the string and its length information
	uint32 getLength() const;
	int8*  getBuffer() const;
	const int8* getText() const;
	uint32 operator[](uint32) const;

	//Several set functions
	void setAt(uint32 _uPos, uint32 _uChar);
	void setText(const CmString&);
	void setLength(uint32);
	void adjustLength(uint32);
	int8* setText(const int8*, const int8*);
	int8* setText(const int8*);

  // Search functions
  int32 findPosition(char ch, uint32 StartPos =0);
  int32 findBackwards(char ch, uint32 StartPos =0);
  int32 searchPattern(const char *Pattern, uint32 StartPos =0);

  // Sub strings
  uint32 assignSubString(uint32 Last, CmString *Src = NULL, uint32 First = 0);

	// Conversion function
	uint32 getNum();

	//Backup and restore
	const int8* read(const int8*);
	void write(const int8*);

	//Constructors and destructors
	CmString();
	CmString(const int8*);
	CmString(const int8*,uint32);
	CmString(uint32);
	CmString(const CmString&);
	virtual ~CmString();

	friend	class CmLString;
	friend	class CmMString;
};

//CmLString represents a list of MStrings
class CmLString : public CmString  
{
public:
	//Functions for handling a list of strings
	CmLString** getAdrNext();
	CmLString* getNext();
	CmString* setNext(CmLString*);
	//Constructor and Destructor
	CmLString();
	virtual ~CmLString();

private:
	CmLString* pNext;
};


//CmMString performs string matching
class CmMString : public CmString  
{
public:
	// Isolate a substring that is delimited by one of a given set 
	//  of delimiter characters starting from an indexed position
	void			resetPosition();
	int8*			getNextDelimitedString();  
	int8*			setDelimiters(int8*);
	const CmString*	setSourceString(const CmString*);
	// Constructor and Destructor
	CmMString(const CmString* pSourceString,const int8* _pszDelimiters =NULL);
	CmMString();
	virtual ~CmMString();

private:
	const CmString*	pSourceString;
	CmString			mSetOfDelimiters;
	uint32			uCurrentPosition;
};

//The MDateTime class allows for storing and processing date and time values.
#define DATETIME_NANOSECONDS  (uint64)(1000*1000*1000)
#define TIMEBASE_SECONDS      (DATETIME_NANOSECONDS)
#define TIMEBASE_MILLISECONDS (DATETIME_NANOSECONDS/1000)
#define TIMEBASE_MICROSECONDS (DATETIME_NANOSECONDS/1000000)
#define TIMEBASE_DAILY        (86400*DATETIME_NANOSECONDS)

class CmDateTime
{
public:
	// Unit test
	int32 unitTest();

	// Systime access function (nanoseconds)
	static int64 getSysClockNanoSec();

	// Time conversion
	static uint64  getNanoSec(const char* szDateTime);
	static CmString getTimeUTC(uint32 uDateTime=0, int32 nDayTime =-1);

  // Timestamp, e.g. as component for filenames
	static CmString getTimestamp(int64 Timestamp, int32 TimeOffset =0, bool WithTime = false);

	// Sidereal time GMST in [pico deg]
	static uint64  getGMST(int64 nUTC);

	//Constructor and Destructor
	CmDateTime();
	virtual ~CmDateTime();

private:
#ifndef __BORLANDC__
#ifdef gcc
	static const uint64 u64J2000		= 0x0D2374199AEA8000ull;
	static const uint64 u64GMST_A		= 0x0000FF13D3880BD0ull;
	static const uint64 u64GMST_B		= 0x000148508547C092ull;
	static const uint64 u64GMST_M		= 0x0001476B081E8000ull;
#else
	static const uint64 u64J2000		= 0x0D2374199AEA8000;
	static const uint64 u64GMST_A		= 0x0000FF13D3880BD0;
	static const uint64 u64GMST_B		= 0x000148508547C092;
	static const uint64 u64GMST_M		= 0x0001476B081E8000;
#endif
	static const uint64 u64MilliArcSec	= 0x0000000000043D12;
#else
	static uint64 u64J2000;
	static uint64 u64GMST_A;
	static uint64 u64GMST_B;
	static uint64 u64GMST_M;
	static uint64 u64MilliArcSec;
#endif
};

/** CmTimestamp
 *  This class represents a timestamp measured in nano-seconds
 */
class CmTimestamp : public CmDateTime
{
public:
  CmTimestamp();
  CmTimestamp(int64 Timestamp_ns);
  ~CmTimestamp();

  /** setTimestamp.
   *  A timestamp value will be assigned and converted if necessary.
   */
  void setTimestamp(int64 Timestamp_ns);
  void setTimestamp(uint64 Timestamp_ns);

  /** getTimestamp.
   *  Currently assigned timestamp value will be returned.
   */
	int64 getTimestamp_ns();
	int64 getTimestamp_us();
	int64 getTimestamp_ms();
	int32 getTimestamp_s();
	// return double [s]
	double getTimestamp();

  /** operator
   *  Some operations with timestamps will be performed
   */
  int64 operator+(int Timestamp_s);
  int64 operator-(int Timestamp_s);
  int64 operator+=(int Period_s);
  int64 operator-=(int Period_s);

	/** getDataRate.
	 *  A data rate will be estimated from the difference of current timestamp
	 *  and the timestamp on initialization.
	 */
	double getDataRate(int DataLength);

private:
  int64 Timestamp_ns;
};

// The benchmark class supports running benchmarks
class MBenchmark
{
private:
	// Time source
	CmDateTime mDateTime;
	// Time variables
	int64 n64CurTime;
	int64 n64TrialEnd;
	int64 n64TrialPeriod;
	// Result variables
	int64 n64Duration;
	int64 n64DurationMin;
	int64 n64ZeroOffset;
	int64 n64ZeroOffsetMin;
	// Loop variables
    int32 nLoops;
	int32 nCurLoop;
	int32 nCycles;
	int32 nCurCycle;
	int32 nTrials;
	int32 nCurTrial;
	// Dummy function
	bool dummy();
public:
	// Running and evaluating a benchmark
	bool run();
	CmString info(int64 nReference=0,int64 n64Divisor=1);

	// Constructors and destructor
	MBenchmark(int32 _nLoops=1000, int32 _nTrialPeriodMilliSec=100, int32 _nTrials=10);
	~MBenchmark();
};

// Exception class used in all modules
class CmException
{
private:
	void* pData;     // data pointer forwarding (no destruction)
	int8* pMessage;  // will be removed in destructor
	int8* pContext;  // will be removed in destructor
public:
	//Constructors and destructor
	CmException();
	CmException(void* _pData);
	CmException(CmString& mMessage);
	CmException(const int8* _pMessage);
	CmException(CmString& mMessage,uint32 _uParameter);
	CmException(const int8* _pMessage,uint32 _uParameter);
	CmException(CmString& mMessage,int32 _nParameter);
	CmException(const int8* _pMessage,int32 _nParameter);
	CmException(CmString& mMessage,uint64 _u64Parameter);
	CmException(const int8* _pMessage,uint64 _u64Parameter);
	CmException(CmString& mMessage,CmString& mContext);
	CmException(const int8* _pMessage,CmString& mContext);
	CmException(const int8* _pMessage,const int8* _pContext);
	CmException(void* _pData,CmString& mMessage);
	CmException(void* _pData,const int8* _pMessage);
	CmException(void* _pData,CmString& mMessage,CmString& mContext);
	CmException(void* _pData,const int8* _pMessage,CmString& mContext);
	CmException(void* _pData,const int8* _pMessage,const int8* _pContext);
 	CmException(const CmException &E);
	~CmException();

	void putMessage(const int8* _pMessage);
	void putContext(const int8* _pContext);

	void* getData();
	int8* getMessage();
	int8* getContext();
};

/** CmUURI
 *  The design of Cosmos software relies on universally unique resource
 *  identifiers (UURI). A UURI is considered to be on the top of any information.
 *  That concept allows for addressing ANY information in a consistent way.
 *  Actually, it also allows for a unification of information, addressing,
 *  references and the like by a single consistent data representation concept.
 *
 *  There are other known concepts like GUID (globally unique identifier, like
 *  e.g. 936DA01F-9ABD-4D9D-80C7-02AF85C822A8) or Internet domain names
 *  (e.g. "wegalink.eu") which may serve as a UURI. However, the concept of a
 *  UURI is more general and therefore it will be defined as a bit field of 
 *  arbitrary length.
 *
 *  Further, the following scheme extends existing identifiers in a way, where
 *  a person, a location and a subject is combined and promises to be as well a
 *  good candidate for being 'universally' unique.
 *
 *  The proposed UURI will be generated in the following way:
 *
 *  <person>@<locator>_<location>.<subject>
 *
 *  The UURI components are defined/described as follows:
 *
 *    <person>   - a person's name or shortcut, e.g. 'Eckhard.Kantz' or 'EKD'
 *    <locator>  - a shortcut reference to a geographical location, e.g. JN58nc
 *                 see also: http://de.wikipedia.org/wiki/QTH-Locator
 *    <location> - a city or another readable location name, e.g. 'Türkenfeld'
 *    <subject>  - any subject designator, e.g. 'Cosmos' for this software
 *
 *  A resulting complete sample UURI would be the following string:
 *
 *    'EKD@JN58nc_Türkenfeld.Cosmos'
 */
#define CM_UURI_COSMOS    "EKD@JN58nc_Türkenfeld.Cosmos"
#define CM_UURI_ANONYMOUS "anonymous@Earth.UURI"
#define CM_UURI_DEFAULT   "Default"
class CmUURI
{
public:
  CmUURI(const char *UURI =NULL, const char *RootUURI =NULL);
  ~CmUURI();

  /** setUURI.
   *  A UURI will be generated by concatenating a RootUURI and a UURI string.
   *  Usually, the user of this function should always provide for a valid UURI.
   *  However, if the UURI string is missing (NULL), then a 'Default' UURI will
   *  be generated. If on the other hand the RootUURI is missing (NULL) then
   *  'anonymous@Earth.UURI' will be used.
   */
  CmReturn setUURI(const char *UURI =NULL, const char *RootUURI =NULL);

  /** operator=/+=
   *  A UURI string will be assigned and accepted without any changes,
   *  respectively a string will be appended.
   */
  void operator=(const char *UURI);
  void operator+=(const char *UURI);

  /** operator==/!=
   *  A UURI will be compared to another UURI.
   */
  bool operator==(const CmUURI& UURI);
  bool operator!=(const CmUURI& UURI);
  bool operator==(const char *UURI);
  bool operator!=(const char *UURI);

  /** getString/Text.
   *  A UURI is made accessable as a constant string or text.
   */
  const CmString& getString() const;
  const char * getText() const;

private:
  // A string representing actual UURI
  CmString UURI;        
};


/** CmXY
 *  This class represents a two dimensional size value consisting of a width and
 *  a height value (or x and y).
 */
template <typename T>
class CmXY
{
  T _x;
  T _y;

public:
  CmXY():_x(0),_y(0){};
  CmXY(T const& x, T const& y):_x(x),_y(y){}
  CmXY(T const& t):_x(t.x),_y(t.y){}
  ~CmXY(){};

public:
  // access functions
  T& x(){ return _x; }
  T& y(){ return _y; }
  T x()const{ return _x; }
  T y()const{ return _y; }

  T & operator=(CmXY const& t)
  {
    if( this!=&t )
    {
      _x = t._x;
      _y = t._y;
    }
  }
};

typedef CmXY<int> CmSize2D;
typedef CmXY<float> CmPoint2D;




}  // namespace Cosmos

using namespace Cosmos;

#endif // ifndef CmTypesH
