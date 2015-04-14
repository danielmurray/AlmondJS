/* 
 * File:   LibAlmondXML.h
 * Author: praveen
 *
 * Created on July 1, 2013, 3:04 PM
 */

#ifndef LIBALMONDXML_H
#define	LIBALMONDXML_H
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

#include "rapidxml.hpp"

//using namespace std;
using namespace rapidxml;

class XmlParse {
public:
    XmlParse();
    ~XmlParse();
    void LoadXml(const char *filename);
    void LoadStringXml(const char *str, const char *filename = "");
    char *GetAttribute(int num, ...);
    int WriteAttribute(int num, ...);
    char *GetElement(int num, ...);
    int WriteElement(int num, ...);
    void UnloadXml(void);
    int deleteNode(int num, ...);
private:
    const char* stralloc(const std::string& str);
    xml_node<>* node(const std::string& name, const std::string& content = "");
    void docDeclaration(void);
    void docCreat(char *root);
    char XmlName[20];
    char temp[50];
    char* chm, *buffer;
    xml_document<> XmlDocArr;

};



#endif	/* LIBALMONDXML_H */

