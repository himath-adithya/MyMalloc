#include "mymalloc.h"

unsigned char memory[MEM_CAP];
unsigned long firstHeapAddress, lastHeapAddress;

void __attribute__((constructor)) initializeMemory()
{
  ((Header *)memory)->is_free = TRUE;
  ((Header *)memory)->size = MEM_CAP - HEADER_SIZE;
  firstHeapAddress = (unsigned long long)&memory;
  lastHeapAddress = (unsigned long long)&memory + MEM_CAP - 1;
}

void *MyMalloc(size_t size)
{
  unsigned short memAddr = 0;
  void *address = NULL;

  if (size <= 0)
    // handle empty block allocation
    return NULL;

  char prevHeaderIsFree = FALSE;
  Header *currentMemoryHeader = NULL, *nextMemoryHeader = NULL, *potentialHeader = NULL;

  while (memAddr < MEM_CAP)
  {
    currentMemoryHeader = (Header *)(memory + memAddr);

    if (currentMemoryHeader->is_free)
    {
      if (!prevHeaderIsFree)
        potentialHeader = currentMemoryHeader;
      else
        potentialHeader->size += currentMemoryHeader->size + HEADER_SIZE;

      if (potentialHeader->size >= size)
      {
        potentialHeader->is_free = FALSE;

        if (potentialHeader->size > size + HEADER_SIZE)
        { // assign next header, if there's memory left from the allocated block
          nextMemoryHeader = (Header *)(memory + memAddr + size + HEADER_SIZE);
          nextMemoryHeader->is_free = TRUE;
          nextMemoryHeader->size = potentialHeader->size - size - HEADER_SIZE;

          potentialHeader->size = size;
        }
        return (void *)potentialHeader + HEADER_SIZE;
      }
      prevHeaderIsFree = TRUE;
    }
    else
    {
      prevHeaderIsFree = FALSE;
    }
    memAddr += currentMemoryHeader->size + HEADER_SIZE;
  }

  return NULL;
}

void MyFree(void *ptr)
{
  Header *temp = (Header *)(ptr - HEADER_SIZE);
  if (ptr != NULL && !temp->is_free && (unsigned long long)ptr >= firstHeapAddress && (unsigned long long)ptr <= lastHeapAddress)
    ((Header *)(ptr - HEADER_SIZE))->is_free = TRUE;
}