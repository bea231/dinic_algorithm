/* 
 * Sergeev Artemiy, 33601/2
 * Dinic's algorithm
 */

#include <stdio.h>

#include "graph.h"

/* Debug memory check support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks()                                         \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));     \
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);              \
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);               \
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#else
  #define SetDbgMemHooks() 0
#endif /* _DEBUG */

#define BEGIN_STR "***********************************\n"
#define END_STR   "***********************************\n\n"

void printMenu( void )
{
  printf("0 - Exit\n"
         "1 - Create and use network\n"
         "2 - Add edge to network\n"
         "3 - Set edge capacity\n"
         "4 - Delete edge from network\n"
         "5 - Get network maximum flow\n"
         "Your choice: ");
}

int main( void )
{
  /* Memory leaks handle function */
  SetDbgMemHooks();
  
  bool canRun = true;
  unsigned int choice = 0;
  flow::network_t *currentNetwork = 0;

  while (canRun)
  {
    printf(BEGIN_STR);
    printMenu();
    scanf("%u%*c", &choice);

    switch (choice)
    {
    case 0:
      canRun = false;
      break;
    case 1:
      unsigned int verticesCount, source, sink;
      char isSure;

      printf("This action will clear current network. Are you sure? (Y/N): ");
      scanf("%c", &isSure);

      if (isSure == 'Y')
      {
        printf("Network vertices count is: ");
        scanf("%u", &verticesCount);
        printf("Network vertices source-vertex number is: ");
        scanf("%u", &source);
        printf("Network vertices sink-vertex number is: ");
        scanf("%u", &sink);

        if (currentNetwork)
          delete currentNetwork;

        currentNetwork = new flow::network_t(verticesCount, source, sink);
      }
      break;
    case 2:
      if (currentNetwork)
      {
        unsigned int from, to, capacity;
        int oldCapacity;

        printf("Edge begin-vertex number will be: ");
        scanf("%u", &from);
        printf("Edge begin-vertex number will be: ");
        scanf("%u", &to);
        printf("Edge capacity will be: ");
        scanf("%u", &capacity);

        oldCapacity = currentNetwork->addEdge(from, to, capacity);
        if (oldCapacity < 0)
          printf("Some error was occured\n");
        else
          printf("Edge was created successfully. Old edge capacity was: %i\n", oldCapacity);
      }
      else
        printf("Try to create network, at first!\n");
      break;
    case 3:
      if (currentNetwork)
      {
        unsigned int from, to, capacity;
        int oldCapacity;

        printf("Edge begin-vertex number is: ");
        scanf("%u", &from);
        printf("Edge begin-vertex number is: ");
        scanf("%u", &to);
        printf("New edge capacity will be: ");
        scanf("%u", &capacity);

        oldCapacity = currentNetwork->setEdgeCapacity(from, to, capacity);
        if (capacity < 0)
          printf("Some error was occured\n");
        else
          printf("New edge capacity was set. Old edge capacity was: %i\n", oldCapacity);
      }
      else
        printf("Try to create network, at first!\n");
      break;
    case 4:
      if (currentNetwork)
      {
        unsigned int from, to;
        int capacity;

        printf("Edge begin-vertex number is: ");
        scanf("%u", &from);
        printf("Edge begin-vertex number is: ");
        scanf("%u", &to);

        capacity = currentNetwork->deleteEdge(from, to);
        if (capacity < 0)
          printf("Some error was occured\n");
        else
          printf("Edge was deleted successfully. Old edge capacity was: %i\n", capacity);
      }
      else
        printf("Try to create network, at first!\n");
      break;
    case 5:
      if (currentNetwork)
      {
        int flow;

        flow = currentNetwork->maximumFlow();
        printf("Maximum network flow is: %i\n", flow);
      }
      else
        printf("Try to create network, at first!\n");
      break;
    }
    printf(END_STR);
  }
  if (currentNetwork)
    delete currentNetwork;
  return 0;
}