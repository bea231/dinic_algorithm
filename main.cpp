/* 
 * Sergeev Artemiy, 33601/2
 * Dinic's algorithm
 */

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

int main( void )
{
  /* Memory leaks handle function */
  SetDbgMemHooks();

  flow::network_t Network(6, 0, 5);

  Network.addEdge(0, 1, 10);
  Network.addEdge(0, 2, 10);
  Network.addEdge(1, 3, 4);
  Network.addEdge(1, 4, 8);
  Network.addEdge(1, 2, 2);
  Network.addEdge(2, 4, 9);
  Network.addEdge(3, 5, 10);
  Network.addEdge(4, 3, 6);
  Network.addEdge(4, 5, 10);


  int flow = Network.maximumFlow();

  return 0;
}