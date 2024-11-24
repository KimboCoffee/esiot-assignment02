#ifndef __DOOR__
#define __DOOR__

class Door {
    public:
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual void openForInsertion() = 0;
        virtual void close() = 0;
        virtual void openForEmptying();
};

#endif