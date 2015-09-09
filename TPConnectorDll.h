// C++ DLL interface, this header must be used by the module
// that wants to access the functionalities of the DLL, You must define the macro DLL_EXPLICIT_LINK if you want to Linking it
// Explicitly, otherwise you are going to link implicitly, you can use in this case the DLL_EXPORTS macro.
// Developer: mariolealfuentes@gmail.com

//Explicit Linking:
//			You must define the macro DLL_EXPLICIT_LINK if you want to Linking Explicitly.


#ifndef TPCONNECTORDLL_H
#define TPCONNECTORDLL_H
#include <string>
#include <map>

class TPCtor_Interface
{
public:
	//To instantiate the object and set the end point and prisma's has string.
	//If return 0, all OK, otherwise return -1
	virtual int TPConnector_Init( const std::string& endPointURL, const std::string& prisma_auth) = 0;
	
	//Payload and Request params are setting with the follow function
	//If return 0, all OK, otherwise return -1
	virtual int SendAuthorizeRequest_SetParams(std::map<std::string, std::string>&RParams, std::map<std::string, std::string>&RPayload) = 0;

	//Web service operation Authorize Request 
	//It sends the request and get the server answer 
	//If return 0, all OK, otherwise return -1
	virtual int SendAuthorizeRequest_Send(std::map<std::string, std::string>&Out) = 0;

	//Web service operation Get Authorize Answer:
	//If return 0, all OK, otherwise return -1
	virtual int GetAuthorizeAnswer_Send(std::map<std::string, std::string>&Input,std:: map<std::string, std::string>&Output) = 0;

	//Web service operation 'Get By OperationId':
	//If return 0, all OK, otherwise return -1
	virtual int GetByOperationId_Send(std::map<std::string, std::string>&Input,std:: map<std::string, std::string>&Output) = 0;

	TPCtor_Interface(){};
	~TPCtor_Interface(){};
};


#ifdef DLL_EXPLICIT_LINK
	// It must be used with GetProcAddress() API after call LoadLibrary().
	typedef TPCtor_Interface* (*PF_GetDLLInterface)();
#else
	#ifdef DLL_EXPORTS
	__declspec(dllexport) TPCtor_Interface* GetDLLInterface();
	#else
	__declspec(dllimport) TPCtor_Interface* GetDLLInterface();
	#endif 
#endif


//SendAuthorizeRequest: the following are the std::map Keys to use with 'RPayload' parameter of SendAuthorizeRequest_SetParams() function. 
const std::string PAYL_MERCHANT = "MERCHANT";
const std::string OPERATIONID	= "OPERATIONID";
const std::string CURRENCYCODE	= "CURRENCYCODE";
const std::string AMOUNT		= "AMOUNT";
const std::string EMAILCLIENTE	= "EMAILCLIENTE";

const std::string CSBTCITY		= "CSBTCITY"; //MANDATORIO.
const std::string CSSTCITY		= "CSSTCITY"; //MANDATORIO.
           
const std::string CSBTCOUNTRY	= "CSBTCOUNTRY";//MANDATORIO. Código ISO.
const std::string CSSTCOUNTRY	= "CSSTCOUNTRY";//MANDATORIO. Código ISO.
             
const std::string CSBTEMAIL		= "CSBTEMAIL"; //MANDATORIO.
const std::string CSSTEMAIL		= "CSSTEMAIL"; //MANDATORIO.
             
const std::string CSBTFIRSTNAME = "CSBTFIRSTNAME";//MANDATORIO.      
const std::string CSSTFIRSTNAME = "CSSTFIRSTNAME";//MANDATORIO.      
             
const std::string CSBTLASTNAME = "CSBTLASTNAME";//MANDATORIO.
const std::string CSSTLASTNAME = "CSSTLASTNAME";//MANDATORIO.
             
const std::string CSBTPHONENUMBER = "CSBTPHONENUMBER";//MANDATORIO.     
const std::string CSSTPHONENUMBER = "CSSTPHONENUMBER";//MANDATORIO.     
             
const std::string CSBTPOSTALCODE = "CSBTPOSTALCODE";//MANDATORIO.
const std::string CSSTPOSTALCODE = "CSSTPOSTALCODE";//MANDATORIO.
             
const std::string CSBTSTATE = "CSBTSTATE";//MANDATORIO
const std::string CSSTSTATE = "CSSTSTATE";//MANDATORIO
             
const std::string CSBTSTREET1 = "CSBTSTREET1";//MANDATORIO.
const std::string CSSTSTREET1 = "CSSTSTREET1";//MANDATORIO.
             
const std::string CSBTCUSTOMERID = "CSBTCUSTOMERID"; //MANDATORIO.
const std::string CSBTIPADDRESS = "CSBTIPADDRESS"; //MANDATORIO.       
const std::string CSPTCURRENCY = "CSPTCURRENCY";//MANDATORIO.      
const std::string CSPTGRANDTOTALAMOUNT = "CSPTGRANDTOTALAMOUNT";//MANDATORIO.
const std::string CSMDD7		= "CSMDD7";//NO MANDATORIO.        
const std::string CSMDD8		= "CSMDD8"; //NO MANDATORIO.       
const std::string CSMDD9		= "CSMDD9";//NO MANDATORIO.       
const std::string CSMDD10		= "CSMDD10";//NO MANDATORIO.      
const std::string CSMDD11		= "CSMDD11";//NO MANDATORIO.
const std::string STCITY		= "STCITY";//MANDATORIO.       
const std::string STCOUNTRY		= "STCOUNTRY";//MANDATORIO.      
const std::string STEMAIL		= "STEMAIL";//MANDATORIO.        
const std::string STFIRSTNAME	= "STFIRSTNAME";//MANDATORIO.        
const std::string STLASTNAME	= "STLASTNAME";//MANDATORIO.      
const std::string STPHONENUMBER = "STPHONENUMBER";//MANDATORIO.        
const std::string STPOSTALCODE	= "STPOSTALCODE";//MANDATORIO.        
const std::string STSTATE		= "STSTATE";//MANDATORIO     
const std::string STSTREET1		= "STSTREET1";//MANDATORIO.       
const std::string CSMDD12		= "CSMDD12";//NO MADATORIO.     
const std::string CSMDD13		= "CSMDD13";//NO MANDATORIO.     
const std::string CSMDD14		= "CSMDD14";//NO MANDATORIO.      
const std::string CSMDD15		= "CSMDD15";//NO MANDATORIO.        
const std::string CSMDD16		= "CSMDD16";//NO MANDATORIO.
const std::string CSITPRODUCTCODE = "CSITPRODUCTCODE";//CONDICIONAL
const std::string CSITPRODUCTDESCRIPTION = "CSITPRODUCTDESCRIPTION";//CONDICIONAL.     
const std::string CSITPRODUCTNAME = "CSITPRODUCTNAME";//CONDICIONAL.  
const std::string CSITPRODUCTSKU = "CSITPRODUCTSKU";//CONDICIONAL.      
const std::string CSITTOTALAMOUNT = "CSITTOTALAMOUNT";//CONDICIONAL.      
const std::string CSITQUANTITY = "CSITQUANTITY";//CONDICIONAL.       
const std::string CSITUNITPRICE = "CSITUNITPRICE";

//SendAuthorizeRequest: the following are the std::map Keys to use with 'RParams' of SendAuthorizeRequest_SetParams() function.
const std::string SECURITY		= "Security";
const std::string SESSION		= "Session";
const std::string MERCHANT		= "MERCHANT";
const std::string URL_OK		= "URL OK";
const std::string URL_ERROR		= "URL Error";
const std::string ENCODING_METHOD = "Encoding Method";

//SendAuthorizeRequest: std::map Keys to use with the return of SendAuthorizeRequest_Send() function.
const std::string STATUSCODE	= "StatusCode";
const std::string Message		= "Message";
const std::string URL_Request	= "URL_Request";
const std::string REQUEST_KEY	= "RequestKey";

//GetAuthorizeAnswer: Inputs Keys to GetAuthorizeAnswer() parameter
const std::string  ANSWER_KEY	= "AnswerKey";

//GetAuthorizeAnswer: std::map Keys to use with the return of GetAuthorizeAnswer_Send()
const std::string  AUTH_KEY		= "AuthorizationKey";
const std::string  ENCOD_METH	= "EncodingMethod";
const std::string  PAYLOAD_ANSWER	= "PayLoadAnswer";

//GetByOperationId: Inputs Keys to  GetByOperationId_Send
const std::string GOPERATION_ID	= "OPERATIONID";

//GetByOperationId: Keys of GetByOperationId_Send() return.
const std::string  OID_RESULTCODE	= "ResultCode";
const std::string  OID_RESULTMESSAGE = "ResultMessage";
const std::string  OID_DATETIME		= "TElapsedSinceEpoch";
const std::string  OID_OPERATIONID	= "OperationID";
const std::string  OID_CURRENCYCODE	= "CurrencyCode";
const std::string  OID_AMOUNT		= "Amount";
const std::string  OID_AMOUNTBUYER	= "AmountBuyer";		
const std::string  OID_BANKID		= "BankAmount";
const std::string  OID_PROMOTIONID	= "PromotionID";
const std::string  OID_TYPE			= "Type";
const std::string  OID_INSTALLMENTPAYMENTS= "INSTALLMENTPAYMENTS";
const std::string  OID_CUSTOMEREMAIL	= "CUSTOMEREMAIL";;		
const std::string  OID_IDENTIFICATIONTYPE= "IDENTIFICATIONTYPE";
const std::string  OID_IDENTIFICATION	= "IDENTIFICATION";
const std::string  OID_CARDNUMBER		= "OID_CARDNUMBER";	

const std::string  OID_CARDHOLDERNAME	= "CARDHOLDERNAME";
const std::string  OID_TICKETNUMBER= "TICKETNUMBER";
const std::string  OID_AUTHORIZATIONCODE= "AUTHORIZATIONCODE";
const std::string  OID_BARCODE= "BARCODE";
const std::string  OID_COUPONEXPDATE= "COUPONEXPDATE";
const std::string  OID_COUPONSECEXPDATE= "COUPONSECEXPDATE";
const std::string  OID_COUPONSUBSCRIBER= "COUPONSUBSCRIBER";	
const std::string  OID_PAYMENTMETHODCODE= "PAYMENTMETHODCODE";;	
const std::string  OID_PAYMENTMETHODNAME= "PAYMENTMETHODNAME";
const std::string  OID_PAYMENTMETHODTYPE= "PAYMENTMETHODTYPE";
const std::string  OID_REFUNDED= "REFUNDED";

#endif /* TPCONNECTORDLL_H */