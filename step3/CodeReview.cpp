/*

NINJARMM Code Review
 
Please review the below code. 
We do not expect you to execute this code, but you are welcome to try. 

Make any code updates that you see fit (If any). 
Comments are encouraged.

*/


struct ThirdPartyAVSoftware
{
    std::wstring Name;
    std::wstring Description;
    std::wstring DefinitionUpdateTime;
    std::string DefinitionStatus;
    std::wstring Version;
    std::wstring ProductState;
};

// replave return type from bool to HRESULT
HRESULT queryWindowsForAVSoftwareDataWSC(std::map<std::wstring, ThirdPartyAVSoftware>& thirdPartyAVSoftwareMap)
{
    HRESULT                         hr              = S_OK; 
    IWscProduct*                    PtrProduct      = nullptr;
    IWSCProductList*                PtrProductList  = nullptr;
    BSTR                            PtrVal          = nullptr;
    LONG                            ProductCount    = 0;
    WSC_SECURITY_PRODUCT_STATE      ProductState;
    WSC_SECURITY_SIGNATURE_STATUS   ProductStatus;

    std::wstring displayName, versionNumber, state, timestamp;
    std::string definitionState;

    //
    // Initialize can only be called once per instance, so you need to
    // CoCreateInstance for each security product type you want to query.
    //
    hr = CoCreateInstance(
            __uuidof(WSCProductList), 
            NULL, 
            CLSCTX_INPROC_SERVER, 
            __uuidof(IWSCProductList), 
            reinterpret_cast<LPVOID*> (&PtrProductList));
    if(FAILED(hr))
    {
        // std::cout << "Failed to create WSCProductList object. ";

        // print error number in hex instead
        std::cout << "CoCreateInstance failed with error: 0x" 
            << std::hex << std::setfill('0') << std::setw(4) 
            << hr << std::endl;
        goto exit;
    }

    //
    // Initialize the product list with the type of security product you're 
    // interested in.
    //
    hr = PtrProductList->Initialize(WSC_SECURITY_PROVIDER_ANTIVIRUS);
    if (FAILED(hr))
    {
        //std::cout << "Failed to query antivirus product list. ";

        // print error number in hex instead
        std::cout << "Initialize failed with error: 0x" 
            << std::hex << std::setfill('0') << std::setw(4) 
            << hr << std::endl;
        goto exit;
    }

    //
    // Get the number of security products of that type.
    //
    hr = PtrProductList->get_Count(&ProductCount);
    if (FAILED(hr))
    {
        //std::cout << "Failed to query product count.";
        
        // print error number in hex instead
        std::cout << "get_Count failed with error: 0x" 
            << std::hex << std::setfill('0') << std::setw(4) 
            << hr << std::endl;
        goto exit;
    }

    //
    // Loop over each product, querying the specific attributes.
    //
    for (uint32_t i = 0; i < ProductCount; i++)
    {
        //
        // Get the next security product
        //
        hr = PtrProductList->get_Item(i, &PtrProduct);
        if (FAILED(hr))
        {
            //std::cout << "Failed to query AV product.";
            //continue;

            // print error number in hex format then goto exit
            std::cout << "get_Item failed with error: 0x" 
                << std::hex << std::setfill('0') << std::setw(4) 
                << hr << std::endl;
            goto exit;
        }

        //
        // Get the product name
        //
        hr = PtrProduct->get_ProductName(&PtrVal);
        if (FAILED(hr))
        {
            // PtrProduct->Release();
            //std::cout << "Failed to query AV product name.";
            //continue;
            
            // print error number in hex format then goto exit
            std::cout << "get_ProductName failed with error: 0x" 
                << std::hex << std::setfill('0') << std::setw(4) 
                << hr << std::endl;
            goto exit;
        }

        displayName = std::wstring(PtrVal, SysStringLen(PtrVal));

        SysFreeString(PtrVal);
        // Set PtrVal to nullptr
        PtrVal = nullptr;
        //
        // Get the product state
        //
        hr = PtrProduct->get_ProductState(&ProductState);
        if (FAILED(hr))
        {
            //std::cout << "Failed to query AV product state.";
            //continue;

            // print error number in hex format then goto exit
            std::cout << "get_ProductState failed with error: 0x" 
                << std::hex << std::setfill('0') << std::setw(4) 
                << hr << std::endl;
            goto exit;
        }

        if (ProductState == WSC_SECURITY_PRODUCT_STATE_ON)
        {
            state = L"On";
        }
        else if (ProductState == WSC_SECURITY_PRODUCT_STATE_OFF)
        {
            state = L"Off";
        }
        else
        {
            state = L"Expired";
        }

        //
        // Get the signature status (not applicable to firewall products)
        //
        hr = PtrProduct->get_SignatureStatus(&ProductStatus);
        if (FAILED(hr))
        {
            //std::cout << "Failed to query AV product definition state.";
            //continue;

            // print error number in hex format then goto exit
            std::cout << "get_SignatureStatus failed with error: 0x" 
                << std::hex << std::setfill('0') << std::setw(4) 
                << hr << std::endl;
            goto exit;
        }

        definitionState = (ProductStatus == WSC_SECURITY_PRODUCT_UP_TO_DATE) ? "UpToDate" : "OutOfDate";

        //
        // Get the product state timestamp (updated when product changes its 
        // state), and only applicable for AV products (NULL is returned for
        // AS and FW products)
        //
        hr = PtrProduct->get_ProductStateTimestamp(&PtrVal);
        if (FAILED(hr))
        {
            //std::cout << "Failed to query AV product definition state.";
            //continue;

            // print error number in hex format then goto exit
            std::cout << "get_ProductStateTimestamp failed with error: 0x" 
                << std::hex << std::setfill('0') << std::setw(4) 
                << hr << std::endl;
            goto exit;
        }
        timestamp = std::wstring(PtrVal, SysStringLen(PtrVal));

        SysFreeString(PtrVal);
        // Set PtrVal to nullptr
        PtrVal = nullptr;

        ThirdPartyAVSoftware thirdPartyAVSoftware;
        thirdPartyAVSoftware.Name = displayName;
        thirdPartyAVSoftware.DefinitionStatus = definitionState;
        thirdPartyAVSoftware.DefinitionUpdateTime = timestamp;
        thirdPartyAVSoftware.Description = state;
        thirdPartyAVSoftware.ProductState = state;
        thirdPartyAVSoftwareMap[thirdPartyAVSoftware.Name] = thirdPartyAVSoftware;

        PtrProduct->Release();
        // Set PtrProduct to nullptr
        PtrProduct = nullptr;
    } // for

    if (thirdPartyAVSoftwareMap.size() == 0)
    {
        hr = E_UNEXPECTED;
    }

exit:

    if (nullptr != PtrVal)
    {
        SysFreeString(PtrVal);
    }
    if (nullptr != PtrProductList)
    {
        PtrProductList->Release();
    }
    if (nullptr != PtrProduct)
    {
        PtrProduct->Release();
    }
    return hr;
}