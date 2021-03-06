/* 
 * File:   SignUtils.cpp
 * Author: Administrator
 * 
 * Created on 2015年8月31日, 下午3:28
 */
#include "stdafx.h"
#include "SignUtils.h"
#include "CryptHelper.h"
#include <iostream>
#include <string.h>


SignUtils::SignUtils() {
}

SignUtils::SignUtils(const SignUtils& orig) {
}

SignUtils::~SignUtils() {
}
/*
 * 在客户端调用登陆接口，得到返回 logintoken 客户端把 logintoken 传给 服务端
 * 服务端组装验证令牌的请求参数：transdata={"appid":"123","logintoken":"3213213"}&sign=xxxxxx&signtype=RSA
 * 请求地址：以文档给出的为准
 */
//int32_t SignUtils::reqData(std::string content,std::string &reqData) {
//     //签名
//    EVP_PKEY* vkey = UTILS::CryptHelper::getKeyByPKCS1(APPV_KEY, 1);
//    if (!vkey) {
//        std::cout << "生成Key异常(error)" << std::endl;
//    }
//
//    std::string reqSign;
//    int32_t ret = UTILS::CryptHelper::md5WithRsa(content, reqSign, vkey);
//    std::cout << "11111"<<SignUtils::UrlUTF8(content.c_str())<< std::endl;
//    if (ret == 0){
//       
//        reqData = "transdata=" + SignUtils::UrlUTF8(content.c_str()) + "&sign=" + SignUtils::UrlUTF8(reqSign.c_str()) + "&signtype=RSA"; // 组装请求参数
//    }
//    return ret;
//}

std::vector<std::string> SignUtils::splitString(const std::string& srcStr, const char ch) {
    std::stringstream ss(srcStr);
    std::string sub;
    std::vector<std::string> resultStringVector;
    while (getline(ss, sub, ch))
    {
        sub.erase(0, sub.find_first_not_of(" \t\n\r"));// 去掉前面多余的空格
        sub.erase(sub.find_last_not_of(" \t\n\r")+1);// 去掉后面多余的空格
        resultStringVector.push_back(sub);
    }    
    return resultStringVector;
}
/*
 * 根据获取到的数据分解出trandata、sign、signtype
 */
void SignUtils::getData(const std::string &respData, std::string &transdata,std::string &sign,std::string &signtype){

    std::vector<std::string> vSplited = splitString(respData, '&');
    for (size_t i = 0; i < vSplited.size(); i++) {
        std::string sub = vSplited.at(i);
         if (sub.compare(0, transdata.size(), transdata) == 0) {
            transdata = sub.substr(sub.find('=') + 1, sub.size());
        } else if (sub.compare(0, sign.size(), sign) == 0) {
            sign = sub.substr(sub.find('=') + 1, sub.size());;
        } else if (sub.compare(0, signtype.size(), signtype) == 0) {
            signtype = sub.substr(sub.find('=') + 1, sub.size());
        }
    }
}
/**
 * 数据验签
 * @param transdata
 * @param sign
 */
//void SignUtils::verifySignData(const std::string transdata, const std::string sign, const std::string signtype){
//    EVP_PKEY* pkey = UTILS::CryptHelper::getKeyByPKCS1(PLATP_KEY, 0);
//    
//     if(0 == UTILS::CryptHelper::verifyMd5WithRsa(transdata, sign, pkey))
//    {
//        std::cout<<"verify sign success"<<std::endl;
//    }
//    else
//    {
//        std::cout<<"verify sign error"<<std::endl;
//    }
//}
struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}
//int32_t SignUtils::curlPost(const std::string& httpUrl, const std::string& postBody, const std::string& encoding,std::string &reqData) {
//    
//  CURL *curl;
//  CURLcode res;
//  struct MemoryStruct chunk;
//  static const char *postthis = postBody.c_str();
//
//  chunk.memory = (char *)malloc(1);  /* will be grown as needed by realloc above */
//  chunk.size = 0;    /* no data at this point */
//
//  curl_global_init(CURL_GLOBAL_ALL);
//  curl = curl_easy_init();
//  if(curl) {
//
//    curl_easy_setopt(curl, CURLOPT_URL, httpUrl.c_str());
//
//    /* send all data to this function  */
//    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
//
//    /* we pass our 'chunk' struct to the callback function */
//    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
//
//    /* some servers don't like requests that are made without a user-agent
//       field, so we provide one */
//    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
//
//    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);
//    
//    curl_slist *plist = curl_slist_append(NULL, ("Content-Type: application/x-www-form-urlencoded; charset=" + encoding).c_str());
//    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);
//
//    /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
//       itself */
//    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
//
//    /* Perform the request, res will get the return code */
//    res = curl_easy_perform(curl);
//    /* Check for errors */
//    if(res != CURLE_OK) {
//      fprintf(stderr, "curl_easy_perform() failed: %s\n",
//              curl_easy_strerror(res));
//    }
//    else {
//      /*
//       * Now, our chunk.memory points to a memory block that is chunk.size
//       * bytes big and contains the remote file.
//       *
//       * Do something nice with it!
//       */
//      printf("%s\n",chunk.memory);
//    }
//    reqData = chunk.memory;
//    /* always cleanup */
//    curl_easy_cleanup(curl);
//
//    free(chunk.memory);
//
//    /* we're done with libcurl, so clean it up */
//    curl_global_cleanup();
//  }
//  return res;
//}
void SignUtils::Gb2312ToUnicode(WCHAR* pOut,const char *gbBuffer)
{
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
	return;
}
void SignUtils::UTF_8ToUnicode(WCHAR* pOut,const char *pText)
{
	char* uchar = (char *)pOut;

	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
	return;
}
void SignUtils::UnicodeToUTF_8(char* pOut,const WCHAR* pText)
{
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char* pchar = (char *)pText;
	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));
	return;
}
void SignUtils::UnicodeToGB2312(char* pOut,const WCHAR uData)
{
	WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(WCHAR),NULL,NULL);
	return;
}
//做为解Url使用
char SignUtils:: CharToInt(const char ch){
	if(ch>='0' && ch<='9')return (char)(ch-'0');
	if(ch>='a' && ch<='f')return (char)(ch-'a'+10);
	if(ch>='A' && ch<='F')return (char)(ch-'A'+10);
	return -1;
}
char SignUtils::StrToBin(const char *str){
	char tempWord[2];
	char chn;
	tempWord[0] = CharToInt(str[0]);                         //make the B to 11 -- 00001011
	tempWord[1] = CharToInt(str[1]);                         //make the 0 to 0 -- 00000000
	chn = (tempWord[0] << 4) | tempWord[1];                //to change the BO to 10110000
	return chn;
}

//UTF_8 转gb2312
void SignUtils::UTF_8ToGB2312(const char *pText, int pLen, std::string &pOut)
{
	char buf[4];
	char* rst = new char[pLen + (pLen >> 2) + 2];
	memset(buf,0,4);
	memset(rst,0,pLen + (pLen >> 2) + 2);
	int i =0;
	int j = 0;

	while(i < pLen)
	{
		if(*(pText + i) >= 0)
		{

			rst[j++] = pText[i++];
		}
		else                 
		{
			WCHAR Wtemp;

			UTF_8ToUnicode(&Wtemp, pText + i);

			UnicodeToGB2312(buf,Wtemp);

			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j+1] = buf[1];
			tmp = rst[j+2] = buf[2];
			//newBuf[j] = Ctemp[0];
			//newBuf[j + 1] = Ctemp[1];
			i += 3;    
			j += 2;   
		}

	}
	rst[j]='\0';
	pOut = rst; 
	delete []rst;
}
//GB2312 转为 UTF-8
void SignUtils::GB2312ToUTF_8(const char *pText, int pLen, std::string& pOut)
{
	char buf[4];
	memset(buf,0,4);
	pOut.clear();
	int i = 0;
	while(i < pLen)
	{
		//如果是英文直接复制就可以
		if( pText[i] >= 0)
		{
			char asciistr[2]={0};
			asciistr[0] = (pText[i++]);
			pOut.append(asciistr);
		}
		else
		{
			WCHAR pbuffer;
			Gb2312ToUnicode(&pbuffer,pText+i);
			UnicodeToUTF_8(buf,&pbuffer);
			pOut.append(buf);
			i += 2;
		}
	}
	return;
}
//把str编码为网页中的 GB2312 url encode ,英文不变，汉字双字节 如%3D%AE%88
std::string SignUtils::UrlGB2312(const char * str)
{
	std::string dd;
	size_t len = strlen(str);
	for (size_t i=0;i<len;i++)
	{
		if(isalnum((BYTE)str[i]))
		{
			char tempbuff[2];
			sprintf_s(tempbuff,"%c",str[i]);
			dd.append(tempbuff);
		}
		else if (isspace((BYTE)str[i]))
		{
			dd.append("+");
		}
		else
		{
			char tempbuff[4];
			sprintf_s(tempbuff, "%%%X%X", ((BYTE*)str)[i] >> 4, ((BYTE*)str)[i] % 16);
			dd.append(tempbuff);
		}
	}
	return dd;
}
//把str编码为网页中的 UTF-8 url encode ,英文不变，汉字三字节 如%3D%AE%88
std::string SignUtils::UrlUTF8(const char * str)
{
	std::string tt;
	std::string dd;
	GB2312ToUTF_8(str,(int)strlen(str), tt);
	size_t len=tt.length();
	for (size_t i=0;i<len;i++)
	{
		if(isalnum((BYTE)tt.at(i)))
		{
			char tempbuff[2]={0};
			sprintf_s(tempbuff, "%c", (BYTE)tt.at(i));
			dd.append(tempbuff);
		}
		else if (isspace((BYTE)tt.at(i)))
		{
			dd.append("+");
		}
		else
		{
			char tempbuff[4];
			sprintf_s(tempbuff, "%%%X%X", ((BYTE)tt.at(i)) >> 4, ((BYTE)tt.at(i)) % 16);
			dd.append(tempbuff);
		}
	}
	return dd;
}
//把url GB2312解码
std::string SignUtils::UrlGB2312Decode(std::string str)
{
	std::string output="";
	char tmp[2];
	int i=0,idx=0,ndx=0,len=str.length();

	while(i<len){
		if(str[i]=='%'){
			tmp[0]=str[i+1];
			tmp[1]=str[i+2];
			output += StrToBin(tmp);
			i=i+3;
		}
		else if(str[i]=='+'){
			output+=' ';
			i++;
		}
		else{
			output+=str[i];
			i++;
		}
	}

	return output;
}
//把url utf8解码
std::string SignUtils::UrlUTF8Decode(std::string str)
{
	std::string output="";
	std::string temp =UrlGB2312Decode(str);//
	UTF_8ToGB2312((char *)temp.data(),strlen(temp.data()), output);
	return output;
}