/* 
 * Sergeev Artemiy, 33601/2
 * Dinic's algorithm
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>

namespace flow
{
  /* Flow network class */
  class network_t
  {
  private:
    /* Vertex neighbour class */
    struct neighbour_t
    {
      unsigned int _id;
      int _capacity, _flow;
      
      /* Default constructor */
      neighbour_t( unsigned int id, int capacity, int flow = 0 ) : _id(id), _capacity(capacity), _flow(flow)
      {
      }
    };

    typedef std::list<neighbour_t> neighbour_list_t;

    /*** Class fields ***/
    neighbour_list_t *_vertices;
    unsigned int      _verticesCount,
                      _edgesCount,
                      _source,
                      _sink;
    /* Default constructor */
    network_t( void ) { }

    neighbour_list_t::iterator placeFor( unsigned int id, unsigned int idWhere );

    /*** Helpful functions for Dinic's algorithm ***/
    bool network_t::dinicBFS( int *distances );
    int  dinicDFS( unsigned int id, int flow, unsigned int *pointers, int *distances  );
  public:
    /* Class constructor for users */
    network_t( unsigned int verticesCount, unsigned int source, unsigned int sink ) : 
        _vertices(0), _verticesCount(verticesCount), _edgesCount(0),
        _source(source), _sink(sink)
    {
      if (verticesCount != 0)
      {
        _vertices = new neighbour_list_t[_verticesCount];
        if (source > _verticesCount || sink > _verticesCount)
          _source = 0, _sink = _verticesCount - 1;
      }
    }

    /* Class destructor */
    ~network_t( void )
    {
      if (_vertices)
        delete[] _vertices;
      _source = _sink = _verticesCount = 0;
    }

    /* Interface for user */
    void clear( void )
    {
      for (unsigned int i = 0; i < _verticesCount; ++i)
      {
        neighbour_list_t::iterator iter = _vertices[i].begin(),
                                   end = _vertices[i].end();

        while (iter != end)
        {
          iter->_flow = 0;
          ++iter;
        }
      }
    }

    /*** Gettters ***/ 
    unsigned int verticesCount( void ) const { return _verticesCount; }
    unsigned int edgesCount( void ) const { return _edgesCount; }

    /*** Functionality ***/
    int addEdge( unsigned int idFrom, unsigned int idTo, int capacity );
    int deleteEdge( unsigned int idFrom, unsigned int idTo );
    int setEdgeCapacity( unsigned int idFrom, unsigned int idTo, int capacity );
    int getEdgeCapacity( unsigned int idFrom, unsigned int idTo );

    int maximumFlow( void );
  };
}

#endif /* _GRAPH_H_ */