#include <iostream>
#include <memory>
#include <atomic>


template<typename T>
class LockFreeQueue {
private:
	struct Node {
		std::shared_ptr<T> myData;
		Node* myNextNode;
		Node() : myNextNode(nullptr) {}
	};

	std::atomic<Node*> myHeadNode;
	std::atomic<Node*> myTailNode;

	Node* popHeadNode() {
		Node* const oldHeadNode = myHeadNode.load();
		if(oldHeadNode == myTailNode.load()) return nullptr;
		myHeadNode.store(oldHeadNode->myNextNode);
		return oldHeadNode;
	}
public:
	LockFreeQueue() : myHeadNode(new Node), myTailNode(myHeadNode.load()) {}
	LockFreeQueue(const LockFreeQueue&) = delete;
	LockFreeQueue& operator=(const LockFreeQueue&) = delete;

	~LockFreeQueue() {
		while(Node* const oldHeadNode = myHeadNode.load()) {
			myHeadNode.store(oldHeadNode->myNextNode);
			delete oldHeadNode;
		}
	}
	
	std::shared_ptr<T> dequeue() {
		Node* oldHeadNode = popHeadNode();
		if(!oldHeadNode) return std::shared_ptr<T>();
		std::shared_ptr<T> const result (oldHeadNode->myData);
		delete oldHeadNode;
		return result;
	}
	void enqueue(T newValue) {
		std::shared_ptr<T> newData(std::make_shared<T>(newValue));
		Node* p = new Node;
		Node* const oldTailNode = myTailNode.load();
		oldTailNode->myData.swap(newData);
		oldTailNode->myNextNode = p;
		myTailNode.store(p);
	}
};
