/* 
 * Sergeev Artemiy, 33601/2
 * Dinic's algorithm
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>

#include <list>
#include <vector>

namespace flow
{
  /* Flow node's neighbour representation type (for adjacency-list) */
  struct neighbour_t
  {
  public:
    unsigned int vertexId;      // identifier of neighbour vertex
    double       edgeCapacity;  // capacity of edge between vertex in adjacency-list and its neighbour

    neighbour_t( unsigned int id = 0, double capacity = 0) : vertexId(id), edgeCapacity(capacity)
    {
    }
  };

  /* Neighbour list type */
  typedef std::list<neighbour_t> neighbour_list_t;

  /* Flow vertex representation class */
  class vertex_t
  {
  private:
    neighbour_list_t _edges;
    unsigned int _edgesCount;
  public:
    /* Class constructor/destructor */
    vertex_t( void ) : _edges(), _edgesCount(0) {}
    ~vertex_t( void ) { _edgesCount = 0; }

    unsigned int edgesCount( void )
    {
      return _edgesCount;
    }

    /* Add edge to vertex function */
    void linkTo( unsigned int vertexNum, double capacity );
    /* Set edge capacity function */
    void setCapacity( unsigned int idTo, double capacity );
    /* Get edge capacity function */
    double getCapacity( unsigned int idTo );
    /* Delete edge function */
    void deleteEdge( unsigned int idTo );

    /* Very bad code (for test) */
    void print( void )
    {
      neighbour_list_t::iterator iter, end = _edges.end();

      for (iter = _edges.begin(); iter != end; ++iter)
        printf("->[%u, %g]", iter->vertexId, iter->edgeCapacity);
    }
  };

  /* Flow network class */
  class network_t
  {
  private:
    vertex_t    *_vertices;      // Adjacency-list of network
    unsigned int _verticesCount; // Count of vertices in network
    unsigned int _edgesCount; // Count of vertices in network
    unsigned int _source, _sink; // id of sink and source of flow network

    /* Private (!) default class constructor */
    network_t( void ) : _vertices(0), _verticesCount(0), _edgesCount(0) {}
  public:
    /* Class constructor */
    network_t( unsigned int verticesCount, unsigned int source, unsigned int sink ) : 
        _verticesCount(verticesCount), _edgesCount(0),
        _source(source >= verticesCount ? 0 : source), _sink(sink >= verticesCount ? _verticesCount - 1 : sink)
    {
      _vertices = new vertex_t[verticesCount];

      if (source == sink)
        _source = 0, _sink = _verticesCount - 1;
    }

    /* Class destructor */
    ~network_t( void )
    {
      if (_vertices)
        delete[] _vertices;
      _source = _sink = _verticesCount = 0;
    }

    /* Getters/setters */
    unsigned int verticesCount( void )
    {
      return _verticesCount;
    }
    unsigned int edgesCount( void )
    {
      return _edgesCount;
    }
    void setEdgeCapacity( unsigned int idFrom, unsigned int idTo, double capacity );
    double getEdgeCapacity( unsigned int idFrom, unsigned int idTo );
    void deleteEdge( unsigned int idFrom, unsigned int idTo );

    /* Very bad code (for test) */
    void print( void )
    {
      printf("Graph:");
      for (unsigned int i = 0; i < _verticesCount; ++i)
      {
        printf("\n[[%u]]", i);
        _vertices[i].print();
      }
      printf("\n");
    }
  };
}

#endif /* _GRAPH_H_ */