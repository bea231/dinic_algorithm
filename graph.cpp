/* 
 * Sergeev Artemiy, 33601/2
 * Dinic's algorithm
 */

#include "graph.h"

using namespace flow;

/* Add edge to vertex function */
void vertex_t::linkTo( unsigned int vertexId, double capacity )
{
  neighbour_t neighbour(vertexId, capacity);
  neighbour_list_t::iterator iter;

  for (iter = _edges.begin(); iter != _edges.end(); ++iter)
  {
    if (iter->vertexId > vertexId)
      break;
    else if (iter->vertexId == vertexId)
      return;
  }
  _edges.insert(iter, neighbour);
}

/* Set edge capacity function */
void vertex_t::setCapacity( unsigned int idTo, double capacity )
{
  if (capacity != 0)  // Set new capacity
  {
    neighbour_list_t::iterator iter, endIter = _edges.end();
    bool isFound = false;

    for (iter = _edges.begin(); iter != endIter; ++iter)
    {
      if (iter->vertexId == idTo)
      {
        isFound = true;
        break;
      }
    }

    if (isFound)
      iter->edgeCapacity = capacity;
    else
      linkTo(idTo, capacity), _edgesCount++;
  }
  else                // Delete edge
  {
    deleteEdge(idTo);
  }
}

/* Get edge capacity function */
double vertex_t::getCapacity( unsigned int idTo )
{
  neighbour_list_t::iterator iter, endIter = _edges.end();
  bool isFound = false;

  for (iter = _edges.begin(); iter != endIter; ++iter)
  {
    if (iter->vertexId == idTo)
    {
      isFound = true;
      break;
    }
  }

  if (isFound)
    return iter->edgeCapacity;
  return 0;
}

/* Delete edge function */
void vertex_t::deleteEdge( unsigned int idTo )
{
  /* Simple functor */
  struct hasId
  {
    unsigned int _id;
    unsigned int &_edgesCount;
    hasId( unsigned int id, unsigned int &count ) : _id(id), _edgesCount(count) {}       // Constructor
    bool operator()( const neighbour_t neigh )  // Check function
    {
      --_edgesCount;
      return neigh.vertexId == _id;
    }
  };
  _edges.remove_if(hasId(idTo, _edgesCount));
}


/* Getters/setters */
void network_t::setEdgeCapacity( unsigned int idFrom, unsigned int idTo, double capacity )
{
  if (idFrom < _verticesCount && idTo < _verticesCount && idFrom != idTo)
  {
    unsigned int oldCount = _vertices[idFrom].edgesCount();
    _vertices[idFrom].setCapacity(idTo, capacity);
    _edgesCount += _vertices[idFrom].edgesCount() - oldCount;
  }
}

double network_t::getEdgeCapacity( unsigned int idFrom, unsigned int idTo )
{
  if (idFrom < _verticesCount && idTo < _verticesCount)
    return _vertices[idFrom].getCapacity(idTo);
  return 0;
}

void network_t::deleteEdge( unsigned int idFrom, unsigned int idTo )
{
  if (idFrom < _verticesCount && idTo < _verticesCount && idFrom != idTo)
  {
    unsigned int oldCount = _vertices[idFrom].edgesCount();
    _vertices[idFrom].deleteEdge(idTo);
    _edgesCount += _vertices[idFrom].edgesCount() - oldCount;
  }
}