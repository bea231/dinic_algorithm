/* 
 * Sergeev Artemiy, 33601/2
 * Dinic's algorithm
 */

#include <queue>

#include <limits.h>

#include "graph.h"

using namespace flow;

network_t::neighbour_list_t::iterator network_t::placeFor( unsigned int id, unsigned int idWhere )
{
  neighbour_list_t::iterator iter = _vertices[idWhere].begin(), 
                             end = _vertices[idWhere].end();

  /* Search a place for new edge */
  while (iter != end)
  {
    if (iter->_id >= id)
      return iter;
    ++iter;
  }
  return iter;
}

void network_t::addEdge( unsigned int idFrom, unsigned int idTo, int capacity )
{
  if (idFrom < _verticesCount && idTo < _verticesCount)
  {
    /* Insert forward edge */
    neighbour_t neigh1(idTo, capacity);
    neighbour_list_t::iterator iter1 = placeFor(idTo, idFrom);

    if (iter1 != _vertices[idFrom].end() && iter1->_id == idTo)
      iter1->_capacity = capacity;
    else
      _vertices[idFrom].insert(iter1, neigh1);

    /* Insert inverse edge with zero capacity */
    neighbour_t neigh2(idFrom, 0);
    neighbour_list_t::iterator iter2 = placeFor(idFrom, idTo);

    if (iter2 != _vertices[idTo].end() &&  iter2->_id == idFrom)
      iter2->_capacity = 0;
    else
      _vertices[idTo].insert(iter2, neigh2);

    _edgesCount += 2;
  }
}

void network_t::deleteEdge( unsigned int idFrom, unsigned int idTo, int capacity )
{
  if (idFrom < _verticesCount && idTo < _verticesCount)
  {
    struct is_equal
    {
      unsigned int _id;
      is_equal( unsigned int id ) : _id(id) { }

      bool operator()( const neighbour_t &neigh ) const
      {
        if (neigh._id == _id)
          return true;
        return false;
      }
    };
    unsigned int size = _vertices[idFrom].size();
    _vertices[idFrom].remove_if(is_equal(idTo));
    _edgesCount += _vertices[idFrom].size() - size;

    size = _vertices[idTo].size();
    _vertices[idTo].remove_if(is_equal(idFrom));
    _edgesCount += _vertices[idTo].size() - size;
  }
}

void network_t::setEdgeCapacity( unsigned int idFrom, unsigned int idTo, int capacity )
{
  if (idFrom < _verticesCount && idTo < _verticesCount)
  {
    neighbour_list_t::iterator iter = placeFor(idFrom, idTo);

    if (iter1 != _vertices[idFrom].end() && iter->_id == idTo)
      iter->_capacity = capacity;
  }
}

int network_t::getEdgeCapacity( unsigned int idFrom, unsigned int idTo )
{
  if (idFrom < _verticesCount && idTo < _verticesCount)
  {
    neighbour_list_t::iterator iter = placeFor(idFrom, idTo);

    if (iter1 != _vertices[idFrom].end() && iter->_id == idTo)
      return iter->_capacity;
  }
  return 0;
}

bool network_t::dinicBFS( int *distances )
{
  /* Set distances for '-1' (unexpected) value */
  std::fill<int *>(distances, distances + _verticesCount, -1);

  /* BFS queue */
  std::queue<unsigned int> Q;

  distances[_source] = 0;
  Q.push(_source);
  do
  {
    unsigned int index = Q.front();
    Q.pop();

    neighbour_list_t::iterator iter = _vertices[index].begin(),
                               end  = _vertices[index].end();

    while (iter != end)
    {
      if (distances[iter->_id] < 0 && iter->_flow < iter->_capacity)
      {
        distances[iter->_id] = distances[index] + 1;
        Q.push(iter->_id);
      }
      ++iter;
    } 

  } while (!Q.empty() && distances[_sink] < 0);

  return distances[_sink] >= 0;
  return false;
}

int  network_t::dinicDFS( unsigned int id, int flow, unsigned int *pointers, int *distances )
{
  if (!flow)
    return 0;
  if (id == _sink)
    return flow;

  /* Get first neighbour to visit */
  neighbour_list_t::iterator iter = _vertices[id].begin();
  for (unsigned int i = 0; i < pointers[id]; ++i)
    ++iter;

  /* Visit neighbours loop */
  for (; pointers[id] < _vertices[id].size(); ++pointers[id], ++iter)
  {
    if (distances[iter->_id] == distances[id] + 1 && iter->_flow < iter->_capacity)
    {
      int pushed = dinicDFS(iter->_id, std::min<int>(flow, iter->_capacity - iter->_flow), pointers, distances );
      if (pushed)
      {
        iter->_flow += pushed;

        iter = placeFor(id, iter->_id);
        iter->_flow -= pushed;
        return pushed;
      }
    }
  }
  return 0;
}

int network_t::maximumFlow( void )
{
  int maxFlow = 0;
  int *distances = new int[_verticesCount];
  unsigned int *pointers = new unsigned int[_verticesCount];

  while (dinicBFS(distances))
  {
    std::fill(pointers, pointers + _verticesCount, '\0');
    while (int pushed = dinicDFS(_source, INT_MAX, pointers, distances))
      maxFlow += pushed;
  }

  delete[] distances;
  delete[] pointers;

  return maxFlow;
}