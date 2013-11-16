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

  /* Simple test */
  flow::network_t g(5, 0, 4);

  g.setEdgeCapacity(0, 1, 0.5);
  printf("Vertices: %u, Edges: %u\n", g.verticesCount(), g.edgesCount());
  g.setEdgeCapacity(0, 1, 0.7);
  printf("Vertices: %u, Edges: %u\n", g.verticesCount(), g.edgesCount());
  g.setEdgeCapacity(1, 0, 0.3);
  printf("Vertices: %u, Edges: %u\n", g.verticesCount(), g.edgesCount());
  g.deleteEdge(0, 1);
  printf("Vertices: %u, Edges: %u\n", g.verticesCount(), g.edgesCount());
  g.deleteEdge(1, 1);
  printf("Vertices: %u, Edges: %u\n", g.verticesCount(), g.edgesCount());
  g.deleteEdge(1, 0);
  printf("Vertices: %u, Edges: %u\n", g.verticesCount(), g.edgesCount());
  g.setEdgeCapacity(1, 0, 0.3);
  g.print();
  printf("\nVertices: %u, Edges: %u", g.verticesCount(), g.edgesCount());

  return 0;
}