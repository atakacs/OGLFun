/**
 * A base class for classes whos' instances are to be used as nodes in a tree.
 */

#ifndef _F_NODE_H_
#define _F_NODE_H_

class Node {
	public: 
		Node() {
			m_parent = m_prev = m_next = m_child = NULL;
		}
		~Node(){} //TODO: Add detachment code here.
		
		bool HasParent() { return m_parent != NULL; }
		bool HasChild() { return m_child != NULL; }
		bool HasNext() { return m_next != NULL; }
		
		Node *FindRoot() {
			return m_parent?m_parent->FindRoot():this;
		}
		/*Node *FindLastSibling() {
			return m_next?m_next->FindLastSibling():this;
		}*/
		//Node *GetNext() { return m_next; }
		//Node *GetPrev() { return m_prev; }
		//Node *GetParent() { return m_parent; }
		
		// Adds a node as child to this node-object.
		void Attach(Node *node) {
			node->m_parent = this;
			node->m_next = NULL;
			node->m_prev = NULL;
			if(m_child) { 
				node->m_next = m_child;
				m_child->m_prev = node;
			}
			m_child = node;
		}
			
	protected:
		Node *m_parent, *m_prev, *m_next, *m_child;
};
#endif /*NODE_H_*/

