/* 
 * File:   Persistence.h
 * Author: ashutosh
 *
 * Created on 21 March, 2014, 2:45 PM
 */

#ifndef PERSISTENCE_H
#define	PERSISTENCE_H

#include<string.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
class Persistence {
public:
    Persistence(char* app_id, char* app_ex);
    virtual ~Persistence();
    void persist(char* volatileLocation, char* filename);
    void depersist(char* filename);
    void copyFile(char* persistentFile, char* location);
private:
    char persistDir[150];
};

#endif	/* PERSISTENCE_H */

