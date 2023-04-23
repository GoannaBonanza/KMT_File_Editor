#include "KMT.h"
#include <fstream>
#include <stdexcept>
//KMTEntry class functions
//for convertinf from little to big and big to little
void KMTEntry::writeShort(unsigned short dc, unsigned char *pos){
    bigEnd.cd=dc;
    pos[0]=bigEnd.c;
    pos[1]=bigEnd.d;
}
void KMTEntry::writeInt(unsigned int dcba, unsigned char *pos){
    bigEnd.abcd=dcba;
    pos[0]=bigEnd.a;
    pos[1]=bigEnd.b;
    pos[2]=bigEnd.c;
    pos[3]=bigEnd.d;
}
unsigned short KMTEntry::getShort(unsigned char *pos) const{
    bigEnd.c=pos[0];
    bigEnd.d=pos[1];
    return bigEnd.cd;
}
unsigned int KMTEntry::getInt(unsigned char *pos) const{
    bigEnd.a=pos[0];
    bigEnd.b=pos[1];
    bigEnd.c=pos[2];
    bigEnd.d=pos[3];
    return bigEnd.abcd;
}
//getters and setters
void KMTEntry::setGamemode(unsigned char gamo){
    entry[0x2]=0;
    entry[0x3]=gamo;
}
void KMTEntry::setCourse(unsigned char course){
    entry[0x4]=course;
}
void KMTEntry::setCharacter(unsigned char character){
    entry[0x5]=character;
}
void KMTEntry::setVehicle(unsigned char vehicle){
    entry[0x6]=vehicle;
}
void KMTEntry::setEngineClass(unsigned char cc){
    entry[0x7]=cc;
}
void KMTEntry::setTimeLimit(unsigned short time){
    writeShort(time, entry+0x2c);
}
void KMTEntry::setScoreRequired(unsigned int score){
    writeInt(score, entry+0x30);
}
void KMTEntry::setCameraMode(unsigned char camera){
    entry[0x48]=0;
    entry[0x49]=camera;
}
void KMTEntry::setCannonFlag(unsigned char cannon){
    entry[0x50]=0;
    entry[0x51]=cannon;
}
//getters here
unsigned char KMTEntry::getGamemode()  const{return entry[0x3];}
unsigned char KMTEntry::getCourse() const{return entry[0x4];}
unsigned char KMTEntry::getChar() const{return entry[0x5];}
unsigned char KMTEntry::getVeh() const{return entry[0x6];}
unsigned char KMTEntry::getCC() const{return entry[0x7];}
unsigned short KMTEntry::getTime()  const{return getShort(entry+0x2c);}
unsigned int KMTEntry::getScore()  const{return getInt(entry+0x30);}
unsigned char KMTEntry::getCamera() const{return entry[0x49];}
unsigned char KMTEntry::getCannon() const{return entry[0x51];}
//CPU settings, not regular getters/setters
bool KMTEntry::addCPU(){
    if(*cpuCount==11) return false;
    *cpuCount+=1;
    return true;
}
void KMTEntry::setCPUVeh(unsigned char vehicle, unsigned int n){
    if(n>*cpuCount) return;
    entry[0x5a+1+n*2]=vehicle;
}
void KMTEntry::setCPUCha(unsigned char character, unsigned int n){
    if(n>*cpuCount) return;
    entry[0x5a+n*2]=character;
}
//pop
bool KMTEntry::popCPU(){
    if(*cpuCount==0) return false;
    *cpuCount-=1;
    return true;
}
//getCPU
unsigned char KMTEntry::getCPUCha(unsigned char n){
    return entry[0x5a+n*2];
}
unsigned char KMTEntry::getCPUVeh(unsigned char n){
    return entry[0x5a+1+n*2];
}
//sets entry pointer to correct pos in data
void KMTEntry::setEntry(unsigned char *ent){
    entry=ent;
    cpuCount=ent+0x59;
}
//KMTFile class functions
//open filename
KMTFile::KMTFile(char *filename){
    open(filename);
}
KMTFile::KMTFile(){
    for(unsigned int j=0; j<0x1c10; j++){
        data[j]=0;
    }
    for(unsigned char i=0; i<64; i++){
        data[0x10+(i*0x70)+1]=i;
        //scrub camera setting
        data[0x10+(i*0x70)+0x48]=0;
        //update default camera from 0 to 3, ignore otherwise
        if(data[0x10+(i*0x70)+0x49]==0) data[0x10+(i*0x70)+0x49]=3;
        //set each entry in entries to their respective entry
        entries[i].setEntry(&data[0x10+(i*0x70)]);
    }
    entry=&entries[0];
}
void KMTFile::open(char *filename){
    if(file.is_open()) file.close();
    file.open(filename);
    if(!file.is_open()) throw std::runtime_error("Unable to open given file");
    file.read(dataR, 0x1c10);
    if(!file) throw std::runtime_error("Error while reading file");
    file.close();
    for(unsigned char i=0; i<64; i++){
        data[0x10+(i*0x70)+1]=i;
        //scrub camera setting
        data[0x10+(i*0x70)+0x48]=0;
        //update default camera from 0 to 3, ignore otherwise
        if(data[0x10+(i*0x70)+0x49]==0) data[0x10+(i*0x70)+0x49]=3;
        //set each entry in entries to their respective entry
        entries[i].setEntry(&data[0x10+(i*0x70)]);
    }
}
//return entry from entries
KMTEntry& KMTFile::operator[](unsigned int ent){
    if(ent>63) throw std::runtime_error("Mission out of range 0-63");
    return entries[ent];
}
//write to file
void KMTFile::writeFile(char *filename){
    std::ofstream ofile(filename, std::ifstream::out);
    if(!ofile.is_open()) throw std::runtime_error("Unable to open given file");
    ofile.seekp(0);
    ofile.write(dataR, 0x1c10);
    file.close();
}
