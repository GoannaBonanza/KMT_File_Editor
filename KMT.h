#ifndef KMT_H
#define KMT_H
#include <fstream>

class KMTEntry{
    private:
    //for conversion to big endian
    union{
        struct{unsigned char d, c, b, a;};
        unsigned short cd;
        unsigned int abcd;
    } mutable bigEnd;
    //points to cpu count in entry once initialized
    unsigned char *cpuCount;
    unsigned char *entry;
    //for ease of editing cpus
    struct{unsigned char chara, vehic;} cpus[11];
    //for writing a small short into 2 big bytes
    void writeShort(unsigned short dc, unsigned char *pos);
    //for writing a small int into a 4 big bytes
    void writeInt(unsigned int dcba, unsigned char *pos);
    //getters that invert
    unsigned int getInt(unsigned char *pos) const;
    unsigned short getShort(unsigned char *pos) const;
    public:
    KMTEntry()=default;
    ~KMTEntry()=default;
    //sets entry pointer, as well as cpu count pos and cpu array positions
    void setEntry(unsigned char *ent);
    //function name explains perfectly, getters and setters
    void setGamemode(unsigned char gamemode);
    void setCourse(unsigned char course);
    void setCharacter(unsigned char character);
    void setVehicle(unsigned char vehicle);
    void setEngineClass(unsigned char cc);
    void setTimeLimit(unsigned short time);
    void setScoreRequired(unsigned int score);
    void setCameraMode(unsigned char camera);
    void setCannonFlag(unsigned char cannon);
    //getters
    unsigned char getGamemode() const;
    unsigned char getCourse() const;
    unsigned char getChar() const;
    unsigned char getVeh() const;
    unsigned char getCC() const;
    unsigned short getTime() const;
    unsigned int getScore() const;
    unsigned char getCamera() const;
    unsigned char getCannon() const;
    //add a new cpu
    bool addCPU();
    void setCPUVeh(unsigned char vehicle, unsigned int n);
    void setCPUCha(unsigned char character, unsigned int n);
    //remove last cpu
    bool popCPU();
    //CPU getters
    unsigned char getCPUCha(unsigned char n);
    unsigned char getCPUVeh(unsigned char n);
    unsigned char cpucount(){return *cpuCount;}
    friend std::ostream& operator<<(std::ostream &os, const KMTEntry &);
};

class KMTFile{
    private:
    char dataR[0x1c10];
    unsigned char *data=(unsigned char *)dataR;
    std::ifstream file;
    KMTEntry entries[0x40], *entry;
    public:
    KMTFile();
    //open kmt file, set all mrXX to good values (00-63), then set each entry in entries
    explicit KMTFile(char *filename);
    //closes file without saving
    void open(char *filename);
    ~KMTFile()=default;
    //get entry
    KMTEntry& operator[](unsigned int ent);
    //writes to kmt file
    void writeFile(char *filename);
};
#endif // KMT_H
