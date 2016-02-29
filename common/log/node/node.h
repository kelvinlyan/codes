#ifndef _LOG_NODE_H
#define _LOG_NODE_H

#include <vector>
#include <string>

#include "../../base/macro.h"
#include "filter.h"

namespace Log
{
	class Node;

	typedef std::vector<Node*> Nodes;

	class State
	{
		public:
			const std::string& severity() const { return _severity; }
			const std::string& tag() const { return _tag; }
			time_t time() const { return _time; }

			void reset(int severity, const std::string& tag, time_t time)
			{
				_severity = severity;
				_tag = tag;
				_time = time;
			}

		private:
			std::string _severity;
			std::string _tag;
			time_t _time;
	};

	class Node
	{
		public:
			Node(): _ft(NULL){}

			virtual ~Node(){}

			void run(const State& state, const std::string& str)
			{
				if(_ft && !_ft->match())
					return;

				std::string re_str = handle(state, str);			
				FOREACH(Nodes, it, _next)
					(*it)->run(state, re_str);
			}

			void setFilter(Filter* ft)
			{
				_ft = ft;
			}
		
			virtual void addSink(Node* n)
			{
				_next.push_back(n);
			}

			virtual std::string handle(const State& state, const std::string& str) = 0;

		private:
			Filter* _ft;
			Nodes _next;
	};
}

#endif
