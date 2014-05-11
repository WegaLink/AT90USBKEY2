//////////////////////////////////////////////////////////////////////////////
//
// CmTypes.cpp: Implementation of basic type classes
//
//////////////////////////////////////////////////////////////////////////////
//
// Author: 	   Eckhard Kantz
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

#include "CmTypes.h"


//////////////////////////////////////////////////////////////////////
// CmUURI Class
//////////////////////////////////////////////////////////////////////
CmUURI::CmUURI(const char *UURI, const char *RootUURI)
{
  // Initialize the UURI string
  setUURI(UURI,RootUURI);

}
CmUURI::~CmUURI()
{

}

CmReturn CmUURI::setUURI(const char *UURI, const char *RootUURI)
{
  // Generate a UURI string
  // NOTE: The user of this function should always specify a valid UURI!
  CmString NewUURI;
  if( NULL!=UURI )
    NewUURI = UURI;
  else
    // Unknown UURI: assign a default UURI (deprecated, although accepted)
    NewUURI = CM_UURI_DEFAULT;

  // Assign a root UURI
  // NOTE: The user of this function should always specify a valid RootUURI!
  if( NULL!=RootUURI )
    this->UURI = RootUURI;
  else
    // Unknown root UURI: use 'anonymous@Earth.UURI' (deprecated, although accepted)
    this->UURI = CM_UURI_ANONYMOUS;

  // Take care for having a single delimiter between root and further UURI string
  if( this->UURI[this->UURI.getLength()-1] == '/' && NewUURI[0] == '/' )
  {
    // remove root string's trailing delimiter (the slash)
    CmString NewRootUURI;
    NewRootUURI.assignSubString(this->UURI.getLength()-2,&this->UURI);
    this->UURI = NewRootUURI;
  }
  else
  if( this->UURI[this->UURI.getLength()-1] != '/' && NewUURI[0] != '/' )
  {
    // extend root string with a delimiter (a slash)
    this->UURI += "/";
  }

  // Save combined UURI assembled from a root UURI and from a UURI string
  this->UURI += NewUURI;

  return Cm_OK;
}

void CmUURI::operator=(const char *newUURI)
{
  // Assign a string as new UURI without any changes 
  UURI = newUURI;
}

void CmUURI::operator+=(const char *UURI)
{
  // Append a string to existing UURI
  this->UURI += UURI;
}

bool CmUURI::operator==(const CmUURI& UURI)
{
  // Check if this UURI's string is equal to another UURI's string
  return this->UURI == UURI.getString();
}

bool CmUURI::operator!=(const CmUURI& UURI)
{
  // Check if this UURI's string is unequal to another UURI's string
  return this->UURI != UURI.getString();
}

bool CmUURI::operator==(const char *UURI)
{
  // Check if this UURI's string is equal to a given string
  return this->UURI == UURI;
}

bool CmUURI::operator!=(const char *UURI)
{
  // Check if this UURI's string is unequal to a given string
  return this->UURI != UURI;
}

const char * CmUURI::getText() const
{
  return UURI.getText();
}
const CmString& CmUURI::getString() const
{
  return UURI;
}



//////////////////////////////////////////////////////////////////////
// CmString Class
//////////////////////////////////////////////////////////////////////

CmString::CmString()
{
  //Reset text array and length
	pText   = NULL;
	uLength = 0;
}

CmString::CmString(const int8* _text)
{
  //Initialize text array
	pText = NULL;
	setText(_text);
}

CmString::CmString(const int8* _text, uint32 _ulength)
{
  // Generate a text array of given buffer length
	uLength = _ulength;
	pText   = new int8[uLength + 1];

  // Copy text to the array and terminate with a '0'
	memcpy(pText,_text,_ulength);
  pText[uLength] = 0;
}

CmString::CmString(const CmString & _String)
{
  //Initialize text array
	pText = NULL;
	setText(_String.getText());
}


CmString::CmString(uint32 _uLength)
{
  //Generate empty text array
	uLength = _uLength;
	pText   = new int8[uLength + 1];
	memset(pText,0,uLength+1);
}

CmString::~CmString()
{
  //Remove text array from heap
	delete[] pText;
}

const int8* CmString::getText() const
{
  //Return text array or empty string
	if(NULL != pText){
		return pText;
	}else{
		return (int8*)"";
	}
}

int8* CmString::getBuffer() const
{
    // Check length and return text array
	if (uLength>0){
		return pText;
	}else{
		return "";
	}
}

uint32 CmString::getLength() const
{
  //Return text length
	return uLength;
}

int8* CmString::setText(const int8* _pText)
{
  //Replace existing text array with a new string
	uLength = (uint32)strlen(_pText);
	delete[] pText;
	pText = new int8[uLength+1];
  if (uLength>0){
	  memcpy(pText,_pText,uLength);
  }
  pText[uLength] = 0;
	return pText;
}

void CmString::setText(const CmString & _String)
{ 
  //Replace existing text array with the content of a given CmString object
	setText(_String.getText());
}

int8* CmString::setText(const int8* pFirst, const int8* pLast)
{
  //Replace existing text array with a given substring
  if (pFirst<=pLast){
	uLength = (uint32)(pLast-pFirst+1);
  }else{
    uLength = 0;
  }
	delete[] pText;
	pText = new int8[uLength+1];
  if (uLength>0){
	  memcpy(pText, pFirst, uLength);
  }
	pText[uLength] = 0;
	return pText;
}

void CmString::setLength(uint32 _uLength)
{
  //Reallocate the text array with a new size
	uLength = _uLength;
	delete[] pText;
	pText = new int8[uLength+1];
  // 2014-02-16/EKantz: clear new data field
  memset(pText,0,uLength+1);
	//*(pText+uLength) = 0;
}

void CmString::adjustLength(uint32 _uLength)
{
  // preserve old text
  uint32 oldLength = uLength;
  int8* oldText = pText;
  // allocate a new text array with new size
	uLength = _uLength;
	pText = new int8[uLength+1];
  // clear new data field
  memset(pText,0,uLength+1);
	// copy old data
  if (uLength <= oldLength)
    memcpy(pText, oldText, uLength);
  else
    memcpy(pText, oldText, oldLength);
  // delete old text array
	delete[] oldText;
}

void CmString::setAt(uint32 _uPos, uint32 _uChar)
{
  //Replace a single character in the text array
	if(_uPos < uLength){
		pText[_uPos] = (int8)_uChar;
	}
}

uint32 CmString::operator[](uint32 _uPos) const
{
  //Return single character at a given position in the text array
	if(_uPos >= uLength){
		return 0;
	}else{
		return pText[_uPos];
	}
}

//CmString& CmString::operator+(CmString RightOperand)
//{
//  // ???????
//  CmString Sum(getText());
//  Sum += RightOperand;
//  return Sum;
//}
//
//CmString& CmString::operator+(const int8* RightOperand)
//{
//  return operator+ (CmString(RightOperand));
//}
//

void CmString::operator += (CmString& mString)
{
	operator += (mString.getBuffer());
}

void CmString::operator += (const int8* pString)
{
	//Preserve existing text array
	int8*  pOldText   = pText;
	uint32 uOldLength = uLength;

	//Add existing and new string into the new text array
	uint32 uStringLength = (uint32)strlen(pString);
	uLength += uStringLength;
	pText = new int8[uLength+1];
	pText[uLength]=0;
	if (uOldLength>0){
		memcpy(pText,pOldText,uOldLength);
	}
	if (uLength>uOldLength){
		memcpy(pText+uOldLength,pString,uStringLength);
	}
	delete[] pOldText;
}

void CmString::operator += (uint32 uNum)
{
	CmString mString;
	mString = uNum;
	operator += (mString.getBuffer());
}

void CmString::operator += (int32 nNum)
{
	CmString mString;
	mString = nNum;
	operator += (mString.getBuffer());
}

void CmString::operator += (uint64 u64Num)
{
	CmString mString;
	mString = u64Num;
	operator += (mString.getBuffer());
}

void CmString::operator = (const CmString& _mString)
{
  //Take over content from a given CmString object
	setText(_mString.getText());	
}

void CmString::operator = (const int8* szString)
{
  //Take over content from a given CmString object
	setText(szString);	
}

void CmString::operator=(const int32 nNum)
{
	char achNum[20];
	SPRINTF4(achNum,sizeof(achNum),"%d",nNum);
	setText(achNum);
}

void CmString::operator=(const uint32 uNum)
{
	char achNum[20];
	SPRINTF4(achNum,sizeof(achNum),"%u",uNum);
	setText(achNum);
}

void CmString::operator=(const uint64 u64Num)
{
#define NUM_BILLION 1000000000
	char achNum[40];
	if (u64Num/NUM_BILLION >= NUM_BILLION){
		SPRINTF6(achNum,sizeof(achNum),"%u%09u%09u",
			(uint32)((u64Num/NUM_BILLION)/NUM_BILLION),
			(uint32)((u64Num/NUM_BILLION)%NUM_BILLION),
			(uint32)(u64Num%NUM_BILLION));
	}else if(u64Num >= NUM_BILLION){
		SPRINTF5(achNum,sizeof(achNum),"%u%09u",
			(uint32)(u64Num/NUM_BILLION),
			(uint32)(u64Num%NUM_BILLION));
	}else{
		SPRINTF4(achNum,sizeof(achNum),"%u",(uint32)u64Num);
	}
	setText(achNum);
}

bool CmString::operator==(const CmString& mTxt)
{
  //Compare the text content of two CmString objects
	if (mTxt.getLength()!=uLength){
		return false;
	}else{
		if (0==strcmp(mTxt.getBuffer(),pText)){
			return true;
		}else{
			return false;
		}
	}
}

bool CmString::operator==(int8* achTxt)
{
  //Compare the text array with a given string
	if (strlen(achTxt)!=uLength){
		return false;
	}else{
		if (0==strcmp(achTxt,pText)){
			return true;
		}else{
			return false;
		}
	}
}

bool CmString::operator!=(const CmString& mTxt)
{
  //Compare the text content of two CmString objects
	if (mTxt.getLength()!=uLength){
		return true;
	}else{
		if (0!=strcmp(mTxt.getBuffer(),pText)){
			return true;
		}else{
			return false;
		}
	}
}

bool CmString::operator!=(int8* achTxt)
{
  //Compare the text array with a given string
	if (strlen(achTxt)!=uLength){
		return true;
	}else{
		if (0!=strcmp(achTxt,pText)){
			return true;
		}else{
			return false;
		}
	}
}

int CmString::compareHeader(const int8* _header)
{
  //Compare the first characters in the text array with a given header string
	return strncmp(pText, _header, strlen(_header));
}

unsigned int CmString::Match(CmLString** ppLMatch, int8 const* pPattern)
{
	int8* pFirst    = pText; //first matching character
	int8* pSrcText  = pText; //current text position
	int8  chMatch = ' ';	 //single character to be found
	int8* szMatch = NULL;	 //group of alternative characters
	uint32 nSkip;			 //skip any character
	uint32 nMatch;		     //current match number
	uint32 nMatchMin;		 //minimal match number
	uint32 nMatchMax;		 //maximal match number
	uint32 nLMatch = 0;	     //number of valid result list members

	for(;;){

		//Evaluate next pattern element
		nSkip   = 0;
		szMatch = NULL;
		switch(*pPattern){
		case 0:
			return nLMatch;
		case '(': 
			pFirst = pSrcText;
			pPattern++;
			continue;
		case ')': 
			if(NULL == *ppLMatch){
				*ppLMatch = new CmLString; 
			}
			(*ppLMatch)->setText(pFirst, pSrcText-1);
			ppLMatch = (*ppLMatch)->getAdrNext();
			nLMatch++;
			pPattern++;
			continue;
		case '.':
			pPattern++;
			//Determine modifiers
			switch(*pPattern){
			case'*':
				nSkip = MAX_UINT32;
				pPattern++;
				break;
			case '+':
				nSkip = MAX_UINT32;
				pSrcText++;
				pPattern++;
			default:
				nSkip = 1;
				break;
			}
			break;
		case '\\':
			pPattern++;
			switch(*pPattern){
			case 's':	//white spaces
				szMatch = " \t\r\n";		
				break;
			case 'd':	//digits
				szMatch = "0123456789";		
				break;
			case 'w':	//word characters
				szMatch = "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ";		
				break;
			default:
				chMatch = *pPattern;
				break;
			}
			pPattern++;
			break;
		default:
			chMatch = *pPattern++;
			break;
		}

		//Determine possible modifiers
		switch(*pPattern){
		case '*':
			nMatchMin = 0;
			nMatchMax = MAX_UINT32;
			pPattern++;
			break;
		case '+':
			nMatchMin = 1;
			nMatchMax = MAX_UINT32;
			pPattern++;
			break;
		case '?':
			nMatchMin = 0;
			nMatchMax = 1;
			pPattern++;
			break;
		default:
			nMatchMin = 1;
			nMatchMax = 1;
			break;
		}

		//Step over matching character(s)
		for(nMatch=0;;){
			if(NULL == szMatch){
				while(nMatch < nMatchMax && chMatch == *pSrcText){
					nMatch++;
					pSrcText++;
				}
			}else{
				while(nMatch < nMatchMax && NULL != strchr(szMatch, (int32)*pSrcText)){
					nMatch++;
					pSrcText++;
				}
			}
			if(nMatch < nMatchMin){
				if(nSkip > nMatch){
					nSkip -= nMatch + 1;
					pSrcText++;
					nMatch = 0;
					continue;
				}
				return nLMatch;
			}
			break;
		}
	}
}

// Search functions
int32 CmString::findPosition(char ch, uint32 StartPos)
{
  // Search for a given character starting at a determined position
  for( uint32 i = StartPos; i < uLength; i++ )
  {
    if( *(pText + i) == ch )
    return i;
  }
  
  // Not found
  return uLength + 1;
}

int32 CmString::findBackwards(char ch, uint32 StartPos)
{
  // Adjust start position
  if( StartPos == 0 )
    StartPos = uLength;

  // Search backwards for a given character starting at a determined position
  for( int32 i = (int)StartPos; i >= 0; i-- )
  {
    if( *(pText + i) == ch )
    return i;
  }
  
  // Not found
  return uLength + 1;
}

// Search pattern
int32 CmString::searchPattern(const char *Pattern, uint32 StartPos)
{
  // Check search range
  if (StartPos>=uLength) return uLength+1; // outside data

  // search for pattern
  char * Found = strstr(pText + StartPos, Pattern);
  if (NULL!=Found) 
    return Found - pText;  // pattern found

  // Try binary search
  uint32 Pos = StartPos;
  while (Pos<uLength){
    Pos = findPosition(*Pattern,Pos);
    if ((Pos<=uLength) && 0==strncmp(pText+Pos,Pattern,strlen(Pattern))) 
      return Pos;  // pattern found
    Pos++;
  }
  return uLength+1; // not found
}


// Sub strings
uint32 CmString::assignSubString(uint32 Last, CmString *Src, uint32 First)
{
  uint32 DstLength;

  // Check for source string
  if( Src == NULL )
    Src = this;

  // Determine actual target length
  if( Src->getLength() <= First )
    DstLength = 0;
  else
  if( Src->getLength() <= Last )
    DstLength = Src->getLength() - First;
  else
  if( Last < First )
    DstLength = 0;
  else
    DstLength = Last - First + 1;

  // Check if the target string is empty
  if( DstLength == 0 )
    setLength(0);
  else
  // Check if the substring is assigned to current string object
  if( Src == this )
  {
    // move current buffer away
    char *OldText = pText;

    // Allocate new buffer
    pText = new char[DstLength + 1];

    // Transfer substring
    memcpy(pText, OldText + First, DstLength);
    *(pText + DstLength) = 0;

    // Delete previous string
    delete[] OldText;
  }
  else
  {
    // Adjust current string length
    setLength(DstLength);

    // Transfer content
    memcpy(pText, Src->pText + First, DstLength);
  }

  return DstLength;
}


// Conversion function
uint32 CmString::getNum()
{
	uint32 uNum = 0;
	for( uint32 i=0; i<getLength(); i++ ){
		uNum *= 10;
		uNum += *(pText+i)-'0';
	}
	return uNum;
}

//Backup and restore
const int8* CmString::read(const int8* pFilename)
{
	FILE*   pFile;
	struct  stat buf;
	int32   fh;
	uint32  uFileSize = 0;

	//Determine file size
#ifdef MSVS
	_sopen_s(&fh, pFilename, O_RDONLY, _SH_DENYWR, 0);
	if (-1 != fh){
		if (0==fstat(fh,&buf)){
			uFileSize = buf.st_size;
		}else{
			throw CmException("File status not accessible.");
		}
		close( fh );
	}else{
		throw CmException("Data file not found.");
	}
#else
	if (-1!=(fh = open(pFilename,O_RDONLY))){
		if (0==fstat(fh,&buf)){
			uFileSize = buf.st_size;
		}else{
			throw CmException("File status not accessible.");
		}
		close( fh );
	}else{
		throw CmException("Data file not found.");
	}
#endif

	#ifdef MSVS
		fopen_s(&pFile, pFilename, "rb");
	#else
		pFile = fopen(pFilename,"rb");
	#endif
	if(NULL==pFile){
		throw CmException("Data file can not be opened.");
	}else{
		try{
			setLength(uFileSize);
			fread(pText,1,uFileSize,pFile);
			fclose(pFile);
		}catch(...){
			fclose(pFile);
			throw CmException("Data file not readable.");
		}
	}
	return pText;
}

void CmString::write(const int8* pFilename)
{
	FILE*   pFile;

	#ifdef MSVS
		fopen_s(&pFile, pFilename, "wb");
	#else
		pFile = fopen(pFilename,"wb");
	#endif


	if (NULL != pFile){
		fwrite(pText,uLength,1,pFile);
		fclose(pFile);
	}else{
		throw CmException("File could not be opened for writing: ",pFilename);
	}
}


//////////////////////////////////////////////////////////////////////
// CmLString Class
//////////////////////////////////////////////////////////////////////
CmLString::CmLString()
{
	pNext = NULL;
}

CmLString::~CmLString()
{

}

CmLString* CmLString::getNext()
{
	return pNext;
}

CmString* CmLString::setNext(CmLString* _Next)
{
	return(pNext = _Next);
}

CmLString** CmLString::getAdrNext()
{
	return &pNext;
}



//////////////////////////////////////////////////////////////////////
// CmMString Class
//////////////////////////////////////////////////////////////////////
CmMString::CmMString(const CmString* _pSourceString,const int8* _pszDelimiters)
{
  if( NULL == _pszDelimiters )
    _pszDelimiters = CM_PATH_DELIMITERS;

	uCurrentPosition = 0;
	mSetOfDelimiters.setText(_pszDelimiters);
	pSourceString = _pSourceString;
}

CmMString::CmMString()
{

}

CmMString::~CmMString()
{
}

void CmMString::resetPosition()
{
	uCurrentPosition = 0;
}

int8* CmMString::getNextDelimitedString()
{
	uint32 uSubStringLength = 0;
	bool   fDelimiterFound  = false;

	//Current position must not be greater than the string length
	if(NULL==pSourceString || uCurrentPosition >= pSourceString->uLength){
		return NULL;
	}
	for(;uCurrentPosition<(*pSourceString).uLength;uCurrentPosition++){
		for(uint32 k=0;k<mSetOfDelimiters.getLength();k++){
			if((uint32)*(pSourceString->getText()+uCurrentPosition) == mSetOfDelimiters[k]){
				fDelimiterFound = true;
				break;
			}
		}
		if(true==fDelimiterFound){
			if(uSubStringLength>0){
				break;
			}
			fDelimiterFound = false;
		}else{
			uSubStringLength++;
		}
	}
	//Transfer substring
	setLength(uSubStringLength);
	for(uint32 m=0;m<uSubStringLength;m++){
		setAt(m, (uint32)*(pSourceString->getText()+uCurrentPosition-uSubStringLength+m));
	}

	return pText;
}

int8* CmMString::setDelimiters(int8* pszDelimiters)
{
	return mSetOfDelimiters.setText(pszDelimiters);
}

const CmString* CmMString::setSourceString(const CmString* _pSourceString)
{
	return pSourceString = _pSourceString;
}



//////////////////////////////////////////////////////////////////////
// CmDateTime class
//////////////////////////////////////////////////////////////////////
CmDateTime::CmDateTime()
{
#ifdef __BORLANDC__
	//u64J2000		    = 0x0D2374199AEA8000;
	//u64GMST_A       = 0x0000FF13D3880BD0;
	//u64GMST_B       = 0x000148508547C092;
	//u64GMST_M       = 0x0001476B081E8000;
	//u64MilliArcSec	= 0x0000000000043D12;
#endif  
}

CmDateTime::~CmDateTime()
{

}

int32 CmDateTime::unitTest()
{
	uint64 u64UTC;
	uint64 u64GMST;
	int32  deltaMilliArcSec;

	printf("CmDateTime unitTest()\n");
	printf("=====================\n\n");

#define DATETIME_TIMESTAMP1		"2005-03-28 18:00:00"
#define DATETIME_TIMESTAMP2		"2038-01-01 12:00:00"
#ifdef gcc
  #define DATETIME_PICO_DEG1		96250441924342ull
  #define DATETIME_PICO_DEG2		281246062475200ull
#else
  #define DATETIME_PICO_DEG1		96250441924342
  #define DATETIME_PICO_DEG2		281246062475200
#endif

	u64UTC = getNanoSec(DATETIME_TIMESTAMP1);	// 06h25m00.106 = 96.250441924342 pico deg (Scientific calculator)
												// 06h25m00.053 = 96.250222119888 pico deg (this algorithm)
												// 06h25m00     = 96.25 deg					http://www.go.ednet.ns.ca/~larry/orbits/jsjdetst.html
												// 06h25m00     = 96.25 deg					http://www.jgiesen.de/astro/astroJS/sunriseJS/
	u64GMST = getGMST(u64UTC);
	deltaMilliArcSec = abs((int32)((u64GMST - DATETIME_PICO_DEG1)/u64MilliArcSec));
	printf("DateTime: %s  ",DATETIME_TIMESTAMP1);
	printf("GMST delta: %5u milli arc sec\n",deltaMilliArcSec);

	u64UTC = getNanoSec(DATETIME_TIMESTAMP2);
	u64GMST = getGMST(u64UTC);
	deltaMilliArcSec = abs((int32)((u64GMST - DATETIME_PICO_DEG2)/u64MilliArcSec));
	printf("DateTime: %s  ",DATETIME_TIMESTAMP2);
	printf("GMST delta: %5u milli arc sec\n\n",deltaMilliArcSec);

	return deltaMilliArcSec;
}

// Systime access function (nanoseconds)
int64 CmDateTime::getSysClockNanoSec()
{
#ifndef WIN32
	struct timeval  stTimeValue;
	struct timezone stTimeZone;
    gettimeofday(&stTimeValue,&stTimeZone);
	return (((int64)1000000000*stTimeValue.tv_sec)+(int64)1000*stTimeValue.tv_usec);
#else
   struct timeb timebuffer;
	#ifdef MSVS
		_ftime_s( &timebuffer );
	#else
		ftime( &timebuffer );
	#endif

   return (int64)1000000*((int64)1000*timebuffer.time+timebuffer.millitm);
#endif
}

// Time conversion
uint64 CmDateTime::getNanoSec(const char* szDateTime)
{
#define TIMEZONE 60*60
	CmString  mDateTime(szDateTime);
	CmMString mNum(&mDateTime," -_:.cdehilmnostu");

	// Date/time components
	time_t	  nTime;
	int32     nMilliSeconds;
	struct tm stDateTime;
	stDateTime.tm_isdst = 0;
	// Year
	mNum.resetPosition();
	if (NULL==mNum.getNextDelimitedString()){
		throw CmException("Invalid year");
	}
	stDateTime.tm_year = mNum.getNum() - 1900;
	// Month
	if (NULL==mNum.getNextDelimitedString()){
		throw CmException("Invalid month");
	}
	stDateTime.tm_mon = mNum.getNum() - 1;
	// Day
	if (NULL==mNum.getNextDelimitedString()){
		throw CmException("Invalid day");
	}
	stDateTime.tm_mday = mNum.getNum();
	// Hour
	if (NULL==mNum.getNextDelimitedString()){
		throw CmException("Invalid hour");
	}
	stDateTime.tm_hour = mNum.getNum();
	// Minute
	if (NULL==mNum.getNextDelimitedString()){
		throw CmException("Invalid minute");
	}
	stDateTime.tm_min = mNum.getNum();
	// Second
	if (NULL==mNum.getNextDelimitedString()){
		throw CmException("Invalid second");
	}
	stDateTime.tm_sec = mNum.getNum();
	// Millisecond
	if (NULL==mNum.getNextDelimitedString()){
		nMilliSeconds = 0;
	}else{
	nMilliSeconds = mNum.getNum();
	}
	// Convert
	if (-1==(nTime=mktime(&stDateTime))){
		throw CmException("Time not recognized",szDateTime);
	}
	return (((uint64)(nTime + TIMEZONE) * 1000) + nMilliSeconds) * 1000000;
}

CmString CmDateTime::getTimeUTC(uint32 uDateTime, int32 nDayTime)
{
	if (0==uDateTime){
		uDateTime = (uint32)time(NULL);
	}

  // Adjust day time (negative = current time)
  if( nDayTime >= 0 )
    uDateTime += nDayTime - uDateTime % (int32)(TIMEBASE_DAILY/TIMEBASE_SECONDS);

	struct tm stDateTime;
	struct tm* pDateTime = &stDateTime;
	#ifdef __BORLANDC__
		pDateTime = gmtime((time_t*)&uDateTime);
	#else
		gmtime_s(pDateTime,(time_t*)&uDateTime);
	#endif
	char achUTC[20];
	SPRINTF9(achUTC, sizeof(achUTC), "%4u-%02u-%02u %02u:%02u:%02u",
		pDateTime->tm_year + 1900,
		pDateTime->tm_mon + 1,
		pDateTime->tm_mday,
		pDateTime->tm_hour,
		pDateTime->tm_min,
		pDateTime->tm_sec);

	return CmString(achUTC);
}

CmString CmDateTime::getTimestamp(int64 Timestamp, int32 TimeOffset, bool WithTime)
{
	char achUTC[256];
  uint32 uDateTime;

  // Generate timestamp [sec.]
	if( 0 == Timestamp ){
		uDateTime = (uint32)time(NULL);
	}else{
    uDateTime = (uint32)(Timestamp/TIMEBASE_SECONDS);
  }

  // Accept a timestamp offset
  uDateTime += TimeOffset;

	// Calculate timestamp components
	struct tm stDateTime;
	struct tm* pDateTime = &stDateTime;
	#ifdef __BORLANDC__
		pDateTime = gmtime((time_t*)&uDateTime);
	#else
		gmtime_s(pDateTime,(time_t*)&uDateTime);
	#endif

  // Generate a timestamp string
  if( WithTime )
  {
    SPRINTF9(achUTC, sizeof(achUTC), "%4u-%02u-%02u_%02u-%02u-%02u",
      pDateTime->tm_year + 1900,
      pDateTime->tm_mon + 1,
      pDateTime->tm_mday,
      pDateTime->tm_hour,
      pDateTime->tm_min,
      pDateTime->tm_sec);
  }
  else
  {
    SPRINTF6(achUTC, sizeof(achUTC), "%4u-%02u-%02u",
      pDateTime->tm_year + 1900,
      pDateTime->tm_mon + 1,
      pDateTime->tm_mday);
  }

	return CmString(achUTC);
}


uint64 CmDateTime::getGMST(int64 n64UTC)
{
	// GMST = 280,460618370000 + 360,985647366290 * d
	// where
	// d = UT days since J2000.0, including parts of a day
	// http://www.xylem.f2s.com/kepler/sidereal.htm
	//
	// 360985647366290 = 0x000148508547C092	[pico deg]
	// 280460618370000 = 0x0000FF13D3880BD0 [pico deg]
	// 360000000000000 = 0x0001476B081E8000 [pico deg]
	//
	// J2000 = ((30*365+7)*24+12)*60*60*1000*1000*1000
	//       = 946728000000000000
	//		 = 0x0D2374199AEA8000
	//
	// MilliArcSec = 1000*1000*1000*1000 / (60*60*1000)
	//			   = 277778
	//		       = 0x0000000000043D12
	//
	// Remarks: Implemented accuracy is about 20 arc sec
	//			in the supported period J2000 +/- 136.
	//			If needed, this can be improved by doing
	//			the multiplication in two parts, a lower
	//			part and a higher part.
	//
#define OVERFLOW_PREVENTION 17
	int64  n64Sec2000;
	uint64 u64GMST;

	// Seconds till epoche 2000 (max +/- 136 years

	// TODO
	n64Sec2000 = (n64UTC - u64J2000)/(1000*1000*1000);
/*
    if (abs64(n64Sec2000) > (uint64)MAX_UINT32){
		throw CmException("Date exceeded range: ",(uint32)abs64(n64Sec2000));
	}
*/
	// sidereal progress since J2000
	u64GMST  = (u64GMST_B >> OVERFLOW_PREVENTION) * n64Sec2000;		// this is the critical multiplication
	u64GMST /= (24*60*60);
	u64GMST <<= OVERFLOW_PREVENTION;
	u64GMST += u64GMST_A;
	u64GMST %= u64GMST_M;
	return u64GMST;
}

//////////////////////////////////////////////////////////////////////
// CmTimestamp class
//////////////////////////////////////////////////////////////////////
CmTimestamp::CmTimestamp()
{
	// initialize timestamp with current time
	Timestamp_ns = getSysClockNanoSec();
}

CmTimestamp::CmTimestamp(int64 Timestamp_ns)
{
  setTimestamp(Timestamp_ns);
}

CmTimestamp::~CmTimestamp()
{

}

void CmTimestamp::setTimestamp(int64 _Timestamp_ns)
{
  Timestamp_ns = _Timestamp_ns;
}

void CmTimestamp::setTimestamp(uint64 _Timestamp_ns)
{
  Timestamp_ns = _Timestamp_ns;
}

int64 CmTimestamp::getTimestamp_ns()
{
  return Timestamp_ns;
}

int64 CmTimestamp::getTimestamp_us()
{
  return Timestamp_ns/1000;
}

int64 CmTimestamp::getTimestamp_ms()
{
  return Timestamp_ns/(1000*1000);
}

int32 CmTimestamp::getTimestamp_s()
{
  return (int)(Timestamp_ns/DATETIME_NANOSECONDS);
}
double CmTimestamp::getTimestamp()
{
	double Timestamp = (double)Timestamp_ns; 
	Timestamp /= DATETIME_NANOSECONDS;

	return Timestamp;
}

int64 CmTimestamp::operator+(int Timestamp_s)
{
  return Timestamp_ns + Timestamp_s * DATETIME_NANOSECONDS;
}

int64 CmTimestamp::operator-(int Timestamp_s)
{
  return Timestamp_ns - Timestamp_s * DATETIME_NANOSECONDS;
}

int64 CmTimestamp::operator+=(int Period_s)
{
  Timestamp_ns += Period_s * DATETIME_NANOSECONDS;
  return Timestamp_ns;
}

int64 CmTimestamp::operator-=(int Period_s)
{
  Timestamp_ns -= Period_s * DATETIME_NANOSECONDS;
  return Timestamp_ns;
}

double CmTimestamp::getDataRate(int DataLength)
{
	// get current timestamp
	CmTimestamp Now;

	// estimate data rate
	double DataRate = Now.getTimestamp();		// end time
	DataRate -= this->getTimestamp();				// minus start time = duration
	if ( DataRate != 0)
		DataRate = DataLength / DataRate;			// amount of data / duration

	return DataRate;
}



//////////////////////////////////////////////////////////////////////
// MBenchmark class
//////////////////////////////////////////////////////////////////////
#define TOLERANCE	  150
#define PRECISION	  10L
#define RANGE_MILLI   1000000L
#define RANGE_MICRO   1000L
#define RANGE_MIN     100L
#define RANGE_MAX     1000000L

MBenchmark::MBenchmark(int32 _nLoops, int32 _nTrialPeriodMilliSec, int32 _nTrials)
{
	nLoops          = _nLoops > 0 ? _nLoops : 1;
	nTrials         = _nTrials > 0 ? _nTrials : 1;
	n64TrialPeriod  = _nTrialPeriodMilliSec > 0 ? _nTrialPeriodMilliSec : 0; 
	n64TrialPeriod  *= 1000000; //convert to nanoseconds
	// Set start condition
	nCurLoop  = 0;
	nCurTrial = 0;
}
MBenchmark::~MBenchmark()
{

}
bool MBenchmark::run()
{
	// Check loop status
	if(--nCurLoop > 0){
		return true;
	}
	// Check for start condition
	if(0==nCurTrial){
		// Initiate new run
		nCycles          = 1;
		nCurLoop         = nLoops;
		nCurTrial        = nTrials;
		n64DurationMin   = MAX_INT64;
		n64ZeroOffsetMin = MAX_INT64;
		n64TrialEnd      = mDateTime.getSysClockNanoSec() + n64TrialPeriod;
		return true;
	}
	// Check for trial end
    if(n64TrialEnd > (n64CurTime = mDateTime.getSysClockNanoSec())){
		nCycles++;
		nCurLoop = nLoops;
		return true;
	}else{
		// Evaluate trial results
		if(nCycles * nLoops != 0){
			n64Duration = (n64TrialPeriod + n64CurTime - n64TrialEnd)* PRECISION / (nCycles * nLoops); 
			// Evaluate empty loop (zero offset)
			nCurLoop   = nLoops;
			nCurCycle  = nCycles;
			n64CurTime = mDateTime.getSysClockNanoSec();
			while(dummy());
			n64TrialEnd   = mDateTime.getSysClockNanoSec();
			n64ZeroOffset = (n64TrialEnd - n64CurTime)* PRECISION / (nCycles * nLoops); 
		}else{
			n64Duration = -1;
		}
		if(n64Duration > 0 && n64Duration < n64DurationMin){
			n64DurationMin = n64Duration;
		}
		if(n64ZeroOffset >= 0 && n64ZeroOffset < n64ZeroOffsetMin){
			n64ZeroOffsetMin = n64ZeroOffset;
		}
		if(--nCurTrial > 0){
			nCycles          = 1;
			nCurLoop         = nLoops;
			n64DurationMin   = MAX_INT64;
			n64ZeroOffsetMin = MAX_INT64;
			n64TrialEnd      = mDateTime.getSysClockNanoSec() + n64TrialPeriod;
			return true;
		}
		return false;
	}
}
bool MBenchmark::dummy()
{
	if(nCurLoop-- > 0){
		return true;
	}
	if(nCurCycle-- > 0){
		nCurLoop = nLoops;
		return true;
	}
	return false;
}
CmString MBenchmark::info(int64 n64Reference,int64 n64Divisor)
{
	int8 achInfo[1000];
	int8 achFlag[1000];

	if(n64Divisor > 1){
		n64DurationMin = (n64DurationMin -n64ZeroOffsetMin) /n64Divisor;
	}else{
		n64DurationMin = n64DurationMin -n64ZeroOffsetMin;
	}
	if((int32)n64DurationMin < (int32)n64Reference){
		SPRINTF3(achFlag, sizeof(achFlag), "--");
	}else if(100*(int32)n64DurationMin > TOLERANCE*(int32)n64Reference){
		SPRINTF3(achFlag, sizeof(achFlag), "++");
	}else{
		SPRINTF3(achFlag, sizeof(achFlag), " ");
	}
	if((int32)n64DurationMin <= 0){
	 // Invalid
		SPRINTF3(achInfo, sizeof(achInfo), "       n.a.         ");
	}else if((int32)(n64DurationMin/(PRECISION*RANGE_MILLI)) > RANGE_MAX){
	 // Range exceeded
		SPRINTF3(achInfo, sizeof(achInfo), "    - out of range -");
	}else if((int32)(n64DurationMin/(PRECISION*RANGE_MILLI)) >= RANGE_MIN && 
	   (int32)(n64DurationMin/RANGE_MILLI) >= 0){
	    // Millisecond range
		SPRINTF6(achInfo, sizeof(achInfo), "%6u ms ref:%6u %s",
			(int32)(n64DurationMin/(PRECISION*RANGE_MILLI)),
			(int32)(n64Reference/(PRECISION*RANGE_MILLI)),
			achFlag);
	}else if((int32)(n64DurationMin/(PRECISION*RANGE_MICRO)) >= RANGE_MIN && 
	   (int32)(n64DurationMin/(RANGE_MICRO*RANGE_MIN)) >= 0){
	    // Microsecond range
		SPRINTF6(achInfo, sizeof(achInfo), "%6u us ref:%6u %s",
			(int32)(n64DurationMin/(PRECISION*RANGE_MICRO)),
			(int32)(n64Reference/(PRECISION*RANGE_MICRO)),
			achFlag);
	}else if((int32)(n64DurationMin/PRECISION) >= RANGE_MIN){
	    // Nanosecond range
		SPRINTF6(achInfo, sizeof(achInfo), "%6u ns ref:%6u %s",
			(int32)(n64DurationMin/PRECISION),
			(int32)(n64Reference/PRECISION),
			achFlag);
	}else{
	    // Sub-nanosecond range
		SPRINTF6(achInfo, sizeof(achInfo), "%6.1f ns ref:%6.1f %s",(float)n64DurationMin/PRECISION,(float)n64Reference/PRECISION,achFlag);
	}
	return CmString(achInfo);
}


//////////////////////////////////////////////////////////////////////
// CmException Class
//////////////////////////////////////////////////////////////////////
CmException::CmException()
{
	pData  = NULL;
	putMessage("General exception encountered");
	putContext("");
}

CmException::CmException(void* _pData)
{
	pData = _pData;
	putMessage("Exception with data encountered");
	putContext("");
}

CmException::CmException(CmString& mMessage)
{
	pData = NULL;
	putMessage(mMessage.getText());
	putContext("");
}

CmException::CmException(const int8* _pMessage)
{
	pData = NULL;
	putMessage(_pMessage);
	putContext("");
}

CmException::CmException(CmString& mMessage,int32 _nParameter)
{
	CmString mParameter;

	pData = NULL;
	putMessage(mMessage.getText());
	mParameter = _nParameter;
	putContext(mParameter.getText());
}

CmException::CmException(const int8* _pMessage,int32 _nParameter)
{
	CmString mParameter;

	pData = NULL;
	putMessage(_pMessage);
	mParameter = _nParameter;
	putContext(mParameter.getText());
}

CmException::CmException(CmString& mMessage,uint32 _uParameter)
{
	CmString mParameter;

	pData = NULL;
	putMessage(mMessage.getText());
	mParameter = _uParameter;
	putContext(mParameter.getText());
}

CmException::CmException(const int8* _pMessage,uint32 _uParameter)
{
	CmString mParameter;

	pData = NULL;
	putMessage(_pMessage);
	mParameter = _uParameter;
	putContext(mParameter.getText());
}

CmException::CmException(CmString& mMessage,uint64 _u64Parameter)
{
	CmString mParameter;

	pData = NULL;
	putMessage(mMessage.getText());
	mParameter = _u64Parameter;
	putContext(mParameter.getText());
}

CmException::CmException(const int8* _pMessage,uint64 _u64Parameter)
{
	CmString mParameter;

	pData = NULL;
	putMessage(_pMessage);
	mParameter = _u64Parameter;
	putContext(mParameter.getText());
}

CmException::CmException(CmString& mMessage,CmString& mContext)
{
	pData = NULL;
	putMessage(mMessage.getText());
	putContext(mContext.getText());
}

CmException::CmException(const int8* _pMessage,CmString& mContext)
{
	pData = NULL;
	putMessage(_pMessage);
	putContext(mContext.getText());
}

CmException::CmException(const int8* _pMessage,const int8* _pContext)
{
	pData = NULL;
	putMessage(_pMessage);
	putContext(_pContext);
}

CmException::CmException(void* _pData,CmString& mMessage)
{
	pData = _pData;
	putMessage(mMessage.getText());
	putContext("");
}
 
CmException::CmException(void* _pData,const int8* _pMessage)
{
	pData = _pData;
	putMessage(_pMessage);
	putContext("");
}
 
CmException::CmException(void* _pData,CmString& mMessage,CmString& mContext)
{
	pData = _pData;
	putMessage(mMessage.getText());
	putContext(mContext.getText());
}
 
CmException::CmException(void* _pData,const int8* _pMessage,CmString& mContext)
{
	pData = _pData;
	putMessage(_pMessage);
	putContext(mContext.getText());
}
 
CmException::CmException(void* _pData,const int8* _pMessage,const int8* _pContext)
{
	pData = _pData;
	putMessage(_pMessage);
	putContext(_pContext);
}
 
CmException::CmException( const CmException &E)
{
	pData = E.pData;
	putMessage(E.pMessage);
	putContext(E.pContext);
}

CmException::~CmException()
{
	delete pMessage;
	delete pContext;
}

void CmException::putMessage(const int8* _pMessage)
{
	int Length = strlen(_pMessage)+1;
	pMessage = new int8[Length]; 
	STRCPY(pMessage, Length, _pMessage);
}

void CmException::putContext(const int8* _pContext)
{
	int Length = strlen(_pContext)+1;
	pContext = new int8[Length]; 
	STRCPY(pContext, Length, _pContext);
}

void* CmException::getData()
{
	return pData;
}

int8* CmException::getMessage()
{
	return pMessage;
}

int8* CmException::getContext()
{
	return pContext;
}

