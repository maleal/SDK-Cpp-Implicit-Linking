# SDK-Cpp-Implicit-Linking
Dll en C++ para transaccionar con el gateway 'Todo Pago', de vinculación Implícita.

# SDK-Cpp-Explicit-Linking
SDK-C++ de Vinculación Implícita

<a name="inicio"></a>		
SDK C++ 	
==================	
		
Modulo de conexión con el gateway de pago 'Todo Pago'	(Dll impementada como interfaz para 'Todo Pago')	

######[Instalación](#instalacion)		
######[Generalidades](#general)	
######[Uso](#uso)
######[Datos adicionales para prevencion de fraude] (#datosadicionales)
######[Status de la operación](#status)


<a name="Instalación"></a>		
## Instalación
<ul>
<li>a. Se debe descargar la última versión del SDK desde el botón Download ZIP, branch master.		
</li>
<li>b. Una vez descargado y descomprimido, debe incluir el archivo TPConnectorDll.h y enlazar la librería        	'IpLinkTPConnectorDll.lib' en su proyecto. Podra definir o no la macro DLL_EXPORTS, con lo cual decidirá si usara 
el atributo dllexport o dllimport en su proyecto.
Si usa Visual C++ 2012  deberá ir a: Property Pages -> C/C++ -> Preprocessor y seleccionar "All Configurations" 
para luego en "Preprocessor Definitios" crear la macro.
</li>
<li>c. Archivo 'cacerts.pem' Contiene los certificados públicos otorgados por una autoridad de certificación de confianza,         puede descargarlo desde
[aqui](http://curl.haxx.se/docs/caextract.html/).
</li>
</ul>

[<sub>Volver a inicio</sub>](#inicio)

<a name="general"></a>
## Generalidades
Esta versión soporta únicamente pago en moneda nacional argentina (CURRENCYCODE = 32).
[<sub>Volver a inicio</sub>](#inicio)

<a name="uso"></a>		
## Uso		
####1.Solo necesita crear un puntero de la clase 'TPCtor_Interface' e inicializarlo con 'GetDLLInterface()' para tener acceso a todos los metodos de la interfáz a Todo Pago:
	Ej:
	
		TPCtor_Interface* pConntor = GetDLLInterface();
		
####2.Inicializar el conector (TodoPago).
	 Para lo cual deberrá llamar a 'TPConnector_Init()' de la siguiente forma
	 -crear un std::string con el Endpoint suministrados por Todo Pago
	 -crear un std::string Athorization con el dato del http header suministrados por Todo Pago
	 -llame al metodo 'TPConnector_Init' Ej:
	 
	 	cout << "---------------- Init TPConnecto .........\n";
		if(ret = pConntor->TPConnector_Init(endPointURL, strAthorization) == 0)
			cout << "---------------- TPConnector_Init() OK\n";
		
####3.Servicio Web 'Authorize Request' (TodoPago).
	Antes de consumir el servicio web "AuthorizeRequest" debemos invocar al método
	"SendAuthorizeRequest_SetParams(request, payload)"
	este metodo usa dos parámetros del tipo std::map, para cada uno de estos parámetros estan definidas
	las keys y se usan de la siguiente forma:
	
		Si 'RParams' es el primer parámetro del metodo, hacemos:
```C++
			std::map<std::string, std::string>RParams;
			
			//datos propios del comercio
			RParams[SECURITY]	= "912EC803B2CE49E4A541068D495AB570";
			RParams[SESSION]	= "ABCDEF-1234-12221-FDE1-00000200";
			RParams[MERCHANT]	= "2153";
			RParams[URL_OK]	= "http://google.com";
			RParams[URL_ERROR]	= "http://www.coco.com";
			RParams[ENCODING_METHOD] = "XML";
```
	        
	        Si 'RPayload' es el segundo parametro de este metodo y también del tipo std:map<string, string>
	        hacemos:
```C++
			map<string, string>PayLParams;
			
			//datos propios del comercio
			PayLParams[EMAILCLIENTE]	= "client_email@dominio.com";
			PayLParams[AMOUNT]		= "55";
			PayLParams[CURRENCYCODE]	= "032";
			PayLParams[OPERATIONID]		= "01";
			PayLParams[PAYL_MERCHANT]	= "2153";
			
			//datos adicionales
			PayLParams[CSBTCITY]		= "Villa General Belgrano"; //MANDATORIO.
			PayLParams[CSSTCITY	]	= "Villa General Belgrano"; //MANDATORIO.
			
			PayLParams[CSBTCOUNTRY]		= "AR";//MANDATORIO. Código ISO.
			PayLParams[CSSTCOUNTRY]		= "AR";//MANDATORIO. Código ISO.
			
			PayLParams[CSBTEMAIL]		= "todopago@hotmail.com"; //MANDATORIO.
			PayLParams[CSSTEMAIL]		= "todopago@hotmail.com"; //MANDATORIO.
			
			PayLParams[CSBTFIRSTNAME]	= "Juan";//MANDATORIO.      
			PayLParams[CSSTFIRSTNAME]	= "Juan";//MANDATORIO.      
			
			PayLParams[CSBTLASTNAME]	= "Perez";//MANDATORIO.
			PayLParams[CSSTLASTNAME]	= "Perez";//MANDATORIO.
			
			PayLParams[CSBTPHONENUMBER]	= "541160913988";//MANDATORIO.     
			PayLParams[CSSTPHONENUMBER]	= "541160913988";//MANDATORIO.     
			
			PayLParams[CSBTPOSTALCODE]	= " 1010";//MANDATORIO.
			PayLParams[CSSTPOSTALCODE]	= " 1010";//MANDATORIO.
			
			PayLParams[CSBTSTATE]		= "B";//MANDATORIO
			PayLParams[CSSTSTATE]		= "B";//MANDATORIO
			
			PayLParams[CSBTSTREET1]		= "Cerrito 740";//MANDATORIO.
			PayLParams[CSSTSTREET1]		= "Cerrito 740";//MANDATORIO.
			
			PayLParams[CSBTCUSTOMERID]	= "453458";; //MANDATORIO.
			PayLParams[CSBTIPADDRESS]	= "192.0.0.4"; //MANDATORIO.       
			PayLParams[CSPTCURRENCY]	= "ARS";//MANDATORIO.      
			PayLParams[CSPTGRANDTOTALAMOUNT]= "125.38";//MANDATORIO.
			PayLParams[CSMDD7		]	="";//NO MANDATORIO.        
			PayLParams[CSMDD8		]	="Y"; //NO MANDATORIO.       
			PayLParams[CSMDD9		]	="";//NO MANDATORIO.       
			PayLParams[CSMDD10		]	="";//NO MANDATORIO.      
			PayLParams[CSMDD11		]	="";//NO MANDATORIO.
			PayLParams[STCITY		]	="rosario";//MANDATORIO.       
			
			PayLParams[STCOUNTRY	]		="";//MANDATORIO.      
			PayLParams[STEMAIL		]	="jose@gmail.com";//MANDATORIO.        
			PayLParams[STFIRSTNAME	]		="Jose";//MANDATORIO.        
			PayLParams[STLASTNAME	]		="Perez";//MANDATORIO.      
			PayLParams[STPHONENUMBER]		= "541155893737";//MANDATORIO.        
			PayLParams[STPOSTALCODE	]		= "1414";//MANDATORIO.        
			PayLParams[STSTATE		]	="D";//MANDATORIO     
			
			PayLParams[STSTREET1	]		="San Martín 123";//MANDATORIO.       
			PayLParams[CSMDD12		]	= "";//NO MADATORIO.     
			PayLParams[CSMDD13		]	= "";//NO MANDATORIO.     
			PayLParams[CSMDD14		]	= "";//NO MANDATORIO.      
			PayLParams[CSMDD15		]	= "";//NO MANDATORIO.        
			PayLParams[CSMDD16		]	= "";//NO MANDATORIO.
			
			PayLParams[CSITPRODUCTCODE] 		= "electronic_good";//CONDICIONAL
			PayLParams[CSITPRODUCTDESCRIPTION]	= "NOTEBOOK L845 SP4304LA DF TOSHIBA";//CONDICIONAL.     
			PayLParams[CSITPRODUCTNAME] 		= "NOTEBOOK L845 SP4304LA DF TOSHIBA";//CONDICIONAL.  
			PayLParams[CSITPRODUCTSKU]		= "LEVJNSL36GN";//CONDICIONAL.      
			PayLParams[CSITTOTALAMOUNT] 		= "1254.40";//CONDICIONAL.      
			PayLParams[CSITQUANTITY]		= "1";//CONDICIONAL.       
			PayLParams[CSITUNITPRICE]		= "1254.40";
			
			cout << "---------------- SendAuthorizeRequest_SetParams()	.........\n";
			if( ret = pConntor->SendAuthorizeRequest_SetParams(RParams, PayLParams) == 0)
				cout << "---------------- SendAuthorizeRequest_SetParams()	OK\n";
```
<ins><strong>Invocamos al servicio web</strong></ins>
		En este caso hay que llamar a SendAuthorizeRequest_Send( Output ). Este metodo devolverá
		en su parámetro  'Output' un std::map<string, string> con las siguientes Keys necesarias
		para ubicar los datos de la respuesta del servicio web.
		
		Out[STATUSCODE]
		Out[Message]
		Out[REQUEST_KEY]
		Out[URL_Request]

```C++
		map<string, string>::iterator it;
		map<string, string>output;
		
		cout << "---------------- SendAuthorizeRequest_Send()	..............\n";
		if( ret = pConntor->SendAuthorizeRequest_Send(output) == 0) {
			cout << "---------------- SendAuthorizeRequest_Send()	OK\n";
			for(it=output.begin(); it != output.end(); it++)
				cout << it->first << " = " << it->second << endl;
		}
```

		
####4.Confirmación de transacción.		
En este caso hay que llamar a GetAuthorizeAnswer_Send(input, output), que lleva dos parámetros map<string, string>. El parámetro 'input' llevara los datos necesario para la transaccion y en 'output' se alogará la respuesta, en el siguiente ejemplose muestra su uso:
```C++
			Inp[SECURITY]	= string("912EC803B2CE49E4A541068D495AB570");
			Inp[SESSION]	= "";
			Inp[MERCHANT]	= string("2153");

			Inp[REQUEST_KEY]= string("dee4d38b-d228-d077-5b55-2b1a12d24a16");
			Inp[ANSWER_KEY] = string("dee4d38b-d228-d077-5b55-2b1a12d24a16");
			
			if( ret = pConntor->GetAuthorizeAnswer_Send(Inp, Out) == 0) {
				cout << Out[STATUSCODE] << endl;
				cout << Out[AUTH_KEY] 	<< endl;
				cout << Out[ENCOD_METH] << endl;
				cout << Out[PAYLOAD_ANSWER] << endl;
			}
```
<a name="datosadicionales"></a>		
## Datos adicionales para control de fraude		

<a name="generales"></a>		
##### Parámetros Adicionales en el post inicial comunes a todos los rubros:
```C++
	//Example
	map<string, string>PayLParams;
	
	PayLParams[CSBTCITY]		= "Villa General Belgrano"; //MANDATORIO.
	PayLParams[CSBTCOUNTRY]		= "AR";//MANDATORIO. Código ISO.
	PayLParams[CSBTEMAIL]		= "todopago@hotmail.com"; //MANDATORIO.
	PayLParams[CSBTFIRSTNAME]	= "Juan";//MANDATORIO.      
	PayLParams[CSBTLASTNAME]	= "Perez";//MANDATORIO.
	PayLParams[CSBTPHONENUMBER]	= "541160913988";//MANDATORIO.     
	PayLParams[CSBTPOSTALCODE]	= " 1010";//MANDATORIO.
	PayLParams[CSBTSTATE]		= "B";//MANDATORIO
	PayLParams[CSBTSTREET1]		= "Cerrito 740";//MANDATORIO.
	PayLParams[CSBTCUSTOMERID]	= "453458";; //MANDATORIO.
	PayLParams[CSBTIPADDRESS]	= "192.0.0.4"; //MANDATORIO.       
	PayLParams[CSPTCURRENCY]	= "ARS";//MANDATORIO.      
	PayLParams[CSPTGRANDTOTALAMOUNT]= "125.38";//MANDATORIO.
	
	PayLParams[CSMDD7		]	="";//NO MANDATORIO.        
	PayLParams[CSMDD8		]	="Y"; //NO MANDATORIO.       
	PayLParams[CSMDD9		]	="";//NO MANDATORIO.       
	PayLParams[CSMDD10		]	="";//NO MANDATORIO.      
	PayLParams[CSMDD11		]	="";//NO MANDATORIO.
```
<a name="retail"></a>		
##### Parámetros Adicionales en el post inicial para el rubro RETAIL		
```C#	
	//Example
	map<string, string>PayLParams;
	
	PayLParams[CSSTCITY	]	= "Villa General Belgrano"; //MANDATORIO.
	PayLParams[CSSTCOUNTRY]		= "AR";//MANDATORIO. Código ISO.
	PayLParams[CSSTEMAIL]		= "todopago@hotmail.com"; //MANDATORIO.
	PayLParams[CSSTFIRSTNAME]	= "Juan";//MANDATORIO.      
	PayLParams[CSSTLASTNAME]	= "Perez";//MANDATORIO.
	PayLParams[CSSTPHONENUMBER]	= "541160913988";//MANDATORIO.     
	PayLParams[CSSTPOSTALCODE]	= " 1010";//MANDATORIO.
	PayLParams[CSSTSTATE]		= "B";//MANDATORIO
	PayLParams[CSSTSTREET1]		= "Cerrito 740";//MANDATORIO.
	PayLParams[CSMDD12	]	= "";//NO MADATORIO.     
	PayLParams[CSMDD13	]	= "";//NO MANDATORIO.     
	PayLParams[CSMDD14	]	= "";//NO MANDATORIO.      
	PayLParams[CSMDD15	]	= "";//NO MANDATORIO.        
	PayLParams[CSMDD16	]	= "";//NO MANDATORIO.
	PayLParams[CSITPRODUCTCODE] 	= "electronic_good";//CONDICIONAL
	PayLParams[CSITPRODUCTDESCRIPTION]= "NOTEBOOK L845 SP4304LA DF TOSHIBA";//CONDICIONAL.  
	PayLParams[CSITPRODUCTNAME] 	= "NOTEBOOK L845 SP4304LA DF TOSHIBA";//CONDICIONAL.  
	PayLParams[CSITPRODUCTSKU]	= "LEVJNSL36GN";//CONDICIONAL.      
	PayLParams[CSITTOTALAMOUNT] 	= "1254.40";//CONDICIONAL.      
	PayLParams[CSITQUANTITY]	= "1";//CONDICIONAL.       
	PayLParams[CSITUNITPRICE]	= "1254.40";
```
<a name="status"></a>
#### Status de la Operación
La SDK cuenta con un m&eacute;todo para consultar el status de la transacci&oacute;n desde la misma SDK. El m&eacute;todo se utiliza de la siguiente manera:
```C++
map<string, string>::iterator it;
map<string, string>Inp;
map<string, string>Out;

// MERCHANT es el id site y GOPERATION_ID es el id operación que se envio en el array a través del método //'sendAuthorizeRequest_Send()´

Inp[GOPERATION_ID] 	= "01";
Inp[MERCHANT]		= "2153";

if( ret = pConntor->GetByOperationId_Send(Inp, Out) == 0 ) {
	cout << "---------------- GetByOperationId_Send() -----	OK\n";
	for(it=Out.begin(); it != Out.end(); it++)
		cout << it->first << " = " << it->second << endl;
}
```
El anterior m&eacute;todo retornara el status actual de la transacci&oacute;n en Todopago, y devuelve en Out un
map<string, string> con el status.

[<sub>Volver a inicio</sub>](#inicio)		


