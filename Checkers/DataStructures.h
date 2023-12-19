
#include<functional>

#ifndef DATASTRUCTURES_H

#define DATASTRUCTURES_H

namespace linear_data_structures
{
	template<class T>
	struct Node
	{
		Node(T data): m_data(data), m_next(nullptr) {}
		
		T& GetData()
		{
			return m_data;
		}

		const T& GetData() const
		{
			return m_data;
		}

		Node<T>* &GetNextPtr()
		{
			return m_next;
		}

	private:
		T m_data;

		Node<T>* m_next;
	};

	template<class T>
	struct single_linked_list 
	{
		single_linked_list():m_head(nullptr), m_count(0) {}

		single_linked_list(const single_linked_list& other) = delete;

		single_linked_list& operator = (const single_linked_list& other) = delete;

        void AddToTheBeginning(T value) {
            Node<T>* newNode = new Node<T>(value);
            newNode->GetNextPtr() = m_head;
            m_head = newNode;

            m_count++;
        }

        void Iterate(std::function<void(T)> func)
        {
            Node<T>* temp = m_head;

            while (temp != nullptr)
            {
                func(temp->GetData());

                temp = temp->GetNextPtr();                
            }
        }
        

        // Function to insert a new node at the end of the list
        void AddToTheEnd(T value) {
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
        

        bool isEmpty()
        {
            return m_head == nullptr;
        }
       
        // Function to delete a node from the linked list
        void RemoveNode(T value) {
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

        // Destructor to deallocate memory
        ~single_linked_list() {
            Clear();
        }

        size_t GetCount()
        {
            return m_count;
        }

        void Clear()
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

        T& operator [] (size_t index)
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

        const T& operator [] (size_t index) const
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

        bool Contains(const T &elem) const
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

#endif // !DATASTRUCTURES_H

