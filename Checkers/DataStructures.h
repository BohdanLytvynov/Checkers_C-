#include<vector>
#include<map>
#include<functional>

#ifndef DATASTRUCTURES_H

#define DATASTRUCTURES_H

namespace linear_data_structures
{
	template<class T>
	struct Node
	{
		Node(T data) : m_data(data), m_next(nullptr) {}

		T& GetData()
		{
			return m_data;
		}

		const T& GetData() const
		{
			return m_data;
		}

		Node<T>*& GetNextPtr()
		{
			return m_next;
		}

	private:
		T m_data;

		Node<T>* m_next;
	};

	template <typename T>
	struct Double_Linked_Node
	{
		//Double_Linked_Node() {}

		Double_Linked_Node(T data) : m_data(data) { m_next = nullptr; m_prev = nullptr; }

		T& GetData() { return m_data; }

		const T& GetData() const { return m_data; }

		Double_Linked_Node<T>*& GetNextPtr() { return m_next; }

		Double_Linked_Node<T>*& GetPrevPtr() { return m_prev; }

	private:
		T m_data;

		Double_Linked_Node<T>* m_next;

		Double_Linked_Node<T>* m_prev;
	};

	template<class T>
	struct doubled_linked_list
	{
		doubled_linked_list() : m_head(nullptr), m_tail(nullptr), m_count(0) {}

		virtual ~doubled_linked_list() { Clear(); }

		virtual void Clear()
		{
			Double_Linked_Node<T>* temp = m_head;
			while (m_head != nullptr) {
				m_head = m_head->GetNextPtr();
				delete temp;
				temp = m_head;
			}

			m_tail = nullptr;

			m_count = 0;
		}

		virtual void AddToTheBegining(T data)
		{			
			Double_Linked_Node<T>* newNodePtr = new Double_Linked_Node<T>(data);

			if (m_head == nullptr && m_tail == nullptr)
			{
				m_head = newNodePtr;

				m_tail = m_head;

				m_count++;

				return;
			}

			newNodePtr->GetNextPtr() = m_head;

			m_head->GetPrevPtr() = newNodePtr;
			
			m_head = newNodePtr;
						
			m_count++;
		}

		virtual void AddToTheEnd(T data)
		{
			Double_Linked_Node<T>* newNodePtr = new Double_Linked_Node<T>(data);

			if (m_head == nullptr && m_tail == nullptr)//List is empty
			{
				m_head = newNodePtr;

				m_tail = m_head;

				m_count++;
			}
			else//Some nodes already exists and we need to add new node to the end
			{
				m_tail->GetNextPtr() = newNodePtr;

				newNodePtr->GetPrevPtr() = m_tail;

				m_tail = newNodePtr;

				m_count++;
			}
		}

		virtual void IterateFromStartToEnd(std::function<bool(T)> iterFunction)
		{
			Double_Linked_Node<T>* temp = m_head;

			while (temp != nullptr)
			{
				if (!iterFunction(temp->GetData()))
				{
					break;
				}

				temp = temp->GetNextPtr();
			}
		}

		virtual void IterateFromEndToStart(std::function<bool(T)> iterFunc)
		{
			Double_Linked_Node<T>* temp = m_tail;

			while (temp != nullptr)
			{
				iterFunc(temp->GetData());

				temp = temp->GetPrevPtr();
			}
		}

		virtual bool isEmpty() const
		{
			return m_head == nullptr;
		}

		virtual size_t GetCount() const
		{
			return m_count;
		}

		virtual bool Contains(const T& key)
		{
			bool contains = false;
		
			this->IterateFromStartToEnd([&contains, key](T data)->bool { 
			
				if (data == key )
				{
					contains = true;

					return false;
				}

				return true;

			});

			return contains;
		}

		virtual void Delete(const T& key)
		{
			if (m_head == nullptr && m_tail == nullptr)
			{
				return;
			}

			Double_Linked_Node<T>* for_delete = nullptr;

			if (m_head->GetData() == key)//Need To delete Head Node
			{
				for_delete = m_head;

				m_head = m_head->GetNextPtr();

				delete for_delete;

				m_count--;
			}
			else if (m_tail->GetData() == key)//Need to delete tail Node 
			{
				for_delete = m_tail;

				m_tail = m_tail->GetPrevPtr();

				delete for_delete;

				m_count--;
			}
			else//Need to delete other node in a list	
			{
				//search for node

				Double_Linked_Node<T>* temp = m_head->GetNextPtr();

				while (temp != m_tail)
				{
					for_delete = temp;

					temp = temp->GetNextPtr();
				}

				if (for_delete != nullptr)//Node for deletion has been found
				{
					for_delete->GetPrevPtr()->GetNextPtr() = for_delete->GetNextPtr()->GetPrevPtr();

					for_delete->GetNextPtr()->GetPrevPtr() = for_delete->GetPrevPtr()->GetNextPtr();

					delete for_delete;

					m_count--;
				}
			}
		}

		doubled_linked_list(const doubled_linked_list<T>& other) = delete;

		doubled_linked_list& operator = (const doubled_linked_list& other) = delete;

	protected:

		Double_Linked_Node<T>* m_head;

		Double_Linked_Node<T>* m_tail;

		size_t m_count;
	};

	template<class T>
	struct circular_doubled_linked_list : public doubled_linked_list<T>
	{
		circular_doubled_linked_list() : doubled_linked_list<T>() {}

		virtual ~circular_doubled_linked_list()
		{
			this->Clear();
		}

		circular_doubled_linked_list(const circular_doubled_linked_list& other) = delete;

		circular_doubled_linked_list& operator = (const circular_doubled_linked_list& other) = delete;

		void Clear() override
		{
			Double_Linked_Node<T>* temp = this->m_head;

			while (this->m_head != nullptr)
			{
				this->m_head = this->m_head->GetNextPtr();
				delete temp;
				temp = this->m_head;
			}

			this->m_tail = nullptr;

			this->m_count = 0;
		}

		void AddToTheBegining(T data) override
		{			
			Double_Linked_Node<T>* newNodePtr = new Double_Linked_Node<T>(data);

			if (this->m_head == nullptr && this->m_tail == nullptr)//List is empty
			{
				this->m_head = newNodePtr;

				this->m_tail = this->m_head;

				this->m_count++;
				
				return;
			}

			newNodePtr->GetNextPtr() = this->m_head;

			this->m_head->GetPrevPtr() = newNodePtr;
		
			newNodePtr->GetPrevPtr() = this->m_tail;

			this->m_tail->GetNextPtr() = newNodePtr;

			this->m_head = newNodePtr;
			
			this->m_count++;
		}

		void AddToTheEnd(T data) override
		{
			Double_Linked_Node<T>* newNodePtr = new Double_Linked_Node<T>(data);

			if (this->m_head == nullptr && this->m_tail == nullptr)//List is empty
			{
				this->m_head = newNodePtr;

				this->m_tail = this->m_head;

				this->m_count++;

				return;
			}

			this->m_tail->GetNextPtr() = newNodePtr;

			newNodePtr->GetPrevPtr() = this->m_tail;

			newNodePtr->GetNextPtr() = this->m_head;

			this->m_head->GetPrevPtr() = newNodePtr;

			this->m_tail = newNodePtr;

			this->m_count++;
		}

		void IterateFromStartToEnd(std::function<bool(T)> iterFunc) override
		{
			Double_Linked_Node<T>* temp = this->m_head;

			if (temp == nullptr)
				return;

			do
			{
				iterFunc(temp->GetData());
				temp = temp->GetNextPtr();

			} while (temp != this->m_head);
		}

		void IterateFromEndToStart(std::function<bool(T)> iterFunc) override
		{
			Double_Linked_Node<T>* temp = this->m_tail;

			if (temp == nullptr)
				return;

			do
			{
				iterFunc(temp->GetData());
				temp = temp->GetPrevPtr();

			} while (temp != this->m_tail);
		}

		bool isEmpty() const override
		{
			return this->m_head == nullptr;
		}

		size_t GetCount() const override
		{
			return this->m_count;
		}

		bool Contains(const T& key) override
		{
			bool contains = false;

			this->IterateFromStartToEnd([&contains, key](T elem)->bool
				{
					if (elem == key)
					{
						contains = true;

						return false;
					}

					return true;
				}
			);

			return contains;
		}

		void Delete(const T& key) override
		{
			Double_Linked_Node<T>* for_delete = nullptr;

			if (this->m_head == nullptr && this->m_tail == nullptr)
			{
				return;
			}

			if (this->m_head->GetData() == key)//Need to delete HEAD
			{
				for_delete = this->m_head;

				this->m_head->GetNextPtr()->GetPrevPtr() = this->m_tail;

				this->m_tail->GetNextPtr() = this->m_head->GetNextPtr();

				delete for_delete;

				this->m_count--;
			}
			else if (this->m_tail->GetData() == key)//Need to delete TAIL
			{
				for_delete = this->m_tail;

				this->m_tail->GetPrevPtr()->GetNextPtr() = this->m_head;

				this->m_head->GetPrevPtr() = this->m_tail->GetPrevPtr();

				delete for_delete;

				this->m_count--;
			}
			else
			{
				Double_Linked_Node<T>* temp = this->m_head;

				do
				{
					for_delete = temp;
					temp = temp->GetNextPtr();

				} while (temp != this->m_head);

				if (for_delete != nullptr)
				{
					for_delete->GetPrevPtr()->GetNextPtr() = for_delete->GetNextPtr();

					for_delete->GetNextPtr()->GetPrevPtr() = for_delete->GetPrevPtr();

					delete for_delete;

					this->m_count--;
				}
			}
		}
	};

	template<class TKey, class TValue>
	struct key_value_pair
	{
#pragma region Ctor
		key_value_pair(TKey key, TValue value)
		{
			m_key = key;

			m_value = value;
		}
#pragma endregion

#pragma region Getters
		const TKey& GetKey()
		{
			return m_key;
		}

		const TValue& GetValue()
		{
			return m_value;
		}
#pragma endregion

#pragma region Operators

		bool operator == (const key_value_pair& other) const
		{
			return other.m_key == this->m_key;
		}

		bool operator != (const key_value_pair& other) const
		{
			return other.m_key != this->m_key;
		}

#pragma endregion

	private:
		TKey m_key;

		TValue m_value;
	};

	template<class T>
	struct single_linked_list
	{
		single_linked_list() :m_head(nullptr), m_count(0) {}

		single_linked_list(const single_linked_list& other) = delete;

		single_linked_list& operator = (const single_linked_list& other) = delete;

		virtual void AddToTheBegining(T value) {
			Node<T>* newNode = new Node<T>(value);
			newNode->GetNextPtr() = m_head;
			m_head = newNode;

			m_count++;
		}

		virtual void Iterate(std::function<bool(T)> func)
		{
			Node<T>* temp = m_head;

			while (temp != nullptr)
			{
				if (!func(temp->GetData()))
				{
					break;
				}

				temp = temp->GetNextPtr();
			}
		}


		// Function to insert a new node at the end of the list
		virtual void AddToTheEnd(T value) {
			Node<T>* newNode = new Node<T>(value);
			if (m_head == nullptr) {
				m_head = newNode;
				m_count++;
				return;
			}

			Node<T>* temp = m_head;
			while (temp->GetNextPtr() != nullptr) {
				temp = temp->GetNextPtr();
			}

			temp->GetNextPtr() = newNode;

			m_count++;
		}


		virtual bool isEmpty()
		{
			return m_head == nullptr;
		}

		// Function to delete a node from the linked list
		virtual void RemoveNode(T value) {
			Node<T>* temp = m_head;
			Node<T>* prev = nullptr;

			// If the node to be deleted is the head
			if (temp != nullptr && temp->GetData() == value) {
				m_head = temp->GetNextPtr();
				delete temp;
				--m_count;
				return;
			}

			// Search for the node to be deleted
			while (temp != nullptr && temp->GetData() != value) {
				prev = temp;
				temp = temp->GetNextPtr();
			}

			// If the value was not found in the list
			if (temp == nullptr) {
				return;
			}

			// Unlink the node from the linked list
			prev->GetNextPtr() = temp->GetNextPtr();
			delete temp;
			--m_count;
		}

		virtual Node<T>* GetNode(T value)
		{
			Node<T>* temp = m_head;

			while (temp != nullptr)
			{
				if (temp->GetData() == value)
				{
					return temp;
				}

				temp = temp->GetNextPtr();
			}

			return nullptr;
		}

		// Destructor to deallocate memory
		virtual ~single_linked_list() {
			Clear();
		}

		size_t GetCount()
		{
			return m_count;
		}

		virtual void Clear()
		{
			Node<T>* temp = m_head;
			while (m_head != nullptr) {
				m_head = m_head->GetNextPtr();
				delete temp;
				temp = m_head;
			}

			m_count = 0;
		}

#pragma region Operators

		virtual T& operator [] (size_t index)
		{
			Node<T>* temp = m_head;

			size_t i = 0;

			while (temp != nullptr)
			{
				if (index == i)
				{
					break;
				}

				temp = temp->GetNextPtr();

				i++;
			}

			return temp->GetData();
		}

		virtual const T& operator [] (size_t index) const
		{
			Node<T>* temp = m_head;

			size_t i = 0;

			while (temp != nullptr)
			{
				if (index == i)
				{
					break;
				}

				temp = temp->GetNextPtr();

				i++;
			}

			return temp->GetData();
		}

		virtual bool Contains(const T& elem) const
		{
			if (m_head == nullptr)
			{
				return false;
			}

			Node<T>* temp = m_head;

			while (temp != nullptr)
			{
				if (temp->GetData() == elem)
				{
					return true;
				}

				temp = temp->GetNextPtr();
			}

			return false;
		}

#pragma endregion


	private:
		Node<T>* m_head;

		size_t m_count;
	};
}


namespace nonlinear_data_structures
{
	template<typename Tkey, typename Tdata>
	struct vertex
	{
		vertex(const Tkey& key, const Tdata& data):m_key(key), m_data(data) {}

		Tkey& GetKey()
		{
			return m_key;
		}

		const Tkey& GetKey() const
		{
			return m_key;
		}

		void SetKey(const Tkey& key)
		{
			m_key = key;
		}

		void SetData(const Tdata& data)
		{
			m_data = data;
		}

		Tdata& GetData()
		{
			return m_data;
		}

		const Tdata& GetData() const
		{
			return m_data;
		}

	private:
		Tkey m_key;

		Tdata m_data;
	};

	template<typename Tkey>
	struct edge
	{
#pragma region Ctor

		edge(const Tkey& from, const Tkey& to):m_from(from), m_to(to) {}

#pragma endregion

#pragma region Getters

		const Tkey& GetFrom() const { return m_from; }

		const Tkey& GetTo() const { return m_to; }

#pragma endregion

#pragma region Setters

		void SetFrom(const Tkey& newFrom) { m_from = newFrom; }

		void SetTo(const Tkey& newTo) { m_to = newTo; }

#pragma endregion

#pragma region Logical Operators

		bool operator == (const edge<Tkey>& other)const
		{
			return (this->m_from == other.m_from) && (this->m_to == other.m_to);
		}

		bool operator != (const edge<Tkey>& other)const
		{
			return !((this->m_from == other.m_from) && (this->m_to == other.m_to));
		}

#pragma endregion

	private:
		Tkey m_from;

		Tkey m_to;
	};

	template<typename Tkey>
	struct edge_list_graph
	{
		edge_list_graph()
		{
			m_graph = new linear_data_structures::doubled_linked_list<edge<Tkey>>();

			m_verteces = new linear_data_structures::single_linked_list<Tkey>();
		}

		virtual ~edge_list_graph()
		{
			m_graph->Clear();

			m_verteces->Clear();

			delete m_graph;

			delete m_verteces;
		}

		virtual void AddEdge(const edge<Tkey>& edge)
		{
			if (!m_verteces->Contains(edge.GetFrom()))
			{
				m_verteces->AddToTheEnd(edge.GetFrom());
			}

			m_graph->AddToTheEnd(edge);			
		}

		virtual void RemoveEdge(const edge<Tkey>& edge)
		{
			m_graph->Delete(edge);			
		}

		std::vector<Tkey> Get_Adjacent_Verteces(const Tkey& vertexKey)
		{
			std::vector<Tkey> result;

			m_graph->IterateFromStartToEnd([&result](edge<Tkey> edge)->bool
				{
					if (edge.GetFrom() == vertexKey)
					{
						result.push_back(edge.GetTo());
					}

					return true;
				}
			);

			return result;
		}

		void depth_first_search(Tkey start, std::function<bool(Tkey Curr_vertex, std::map<Tkey, bool>)> dir_call = nullptr,
			std::function<bool(Tkey Curr_vertex)> rec_CallBack = nullptr)
		{
			std::map<Tkey, bool> v_d = generate_visit_dictionary();

			dfs(start, v_d, dir_call, rec_CallBack);
		}

		std::map<Tkey, bool> generate_visit_dictionary()
		{
			std::map<Tkey, bool> v_d = std::map<Tkey, bool>(m_verteces->GetCount());

			m_verteces->Iterate([&v_d](Tkey elem)->bool
				{
					v_d[elem] = false;

					return true;
				});

			return v_d;
		}

	private:

		void dfs(Tkey start, std::map<Tkey, bool>& v_d, 
			std::function<bool (Tkey Curr_vertex, std::map<Tkey, bool>)> dir_call = nullptr,
			std::function<bool (Tkey Curr_vertex)> rec_CallBack = nullptr)
		{
			v_d[start] = true;

			if (dir_call != nullptr)
				if (!dir_call(start, v_d))
					return;

			std::vector<Tkey> adjVerteces = this->Get_Adjacent_Verteces(start);

			for (auto next : adjVerteces)
			{
				if (v_d[next] == false)
				{
					dfs(next, v_d, dir_call, rec_CallBack);
				}
			}

			if (rec_CallBack != nullptr)
				if (!rec_CallBack(start))
					return;
		}

		linear_data_structures::doubled_linked_list<edge<Tkey>>* m_graph;

		linear_data_structures::single_linked_list<Tkey>* m_verteces;		
	};

	template<typename Tkey, typename Tdata>
	struct edge_list_graph_with_data : public edge_list_graph<Tkey>
	{
#pragma region Ctor

		edge_list_graph_with_data() : edge_list_graph<Tkey>() 
		{
			m_vertex_data = new linear_data_structures::single_linked_list<linear_data_structures::key_value_pair<Tkey, Tdata>>();
		}
	
#pragma endregion

#pragma region Destructor

		~edge_list_graph_with_data() override
		{
			edge_list_graph<Tkey>::~edge_list_graph();

			m_vertex_data->Clear();

			delete m_vertex_data;
		}

#pragma endregion

#pragma region Functions

		void AddData(Tkey key, Tdata data)
		{
			linear_data_structures::key_value_pair<Tkey, Tdata> pair = 
				linear_data_structures::key_value_pair<Tkey, Tdata>(key, data);

			if (!m_vertex_data->Contains(key))
			{
				m_vertex_data->AddToTheEnd(pair);
			}			
		}

#pragma endregion


	private:
		linear_data_structures::single_linked_list<linear_data_structures::key_value_pair<Tkey, Tdata>>* m_vertex_data;
	};

}

#endif // !DATASTRUCTURES_H
