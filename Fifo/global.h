#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct // create struct that will be values that are hold in queue
{
  int key;
  int* pTab;
}QInfo;

#define QINFO QInfo // define QINFO which is connected with struct above

#endif