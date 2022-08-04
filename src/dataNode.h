#pragma once

struct dataNode
{
	int value;
	dataNode* next = nullptr;
};

void addElement(int value, dataNode** headRef) {
	while ((*headRef) != nullptr)
	{
		headRef = &(*headRef)->next;
	}
	(*headRef) = new dataNode;
	(*headRef)->value = value;
} 

bool deleteElement(unsigned int elementPosition, dataNode** headRef) {
	int i = 0;
	bool hasBeenDeleted = false;
	dataNode** list = headRef;
	

	while (*list)
	{
		dataNode* ptrToDelete = *list;
		
		if (i == elementPosition) {
			*list = ptrToDelete->next;
			delete ptrToDelete;
			return true;
		}
		else {
			list = &(*list)->next;
		}
		i++;
	}
	return false;
}

bool modifyElement(int position, int value, dataNode** headRef) {
	int i = 0;
	while ((*headRef) != nullptr)
	{
		if (position == i)
		{
			(*headRef)->value = value;
			return true;
		}
		headRef = &(*headRef)->next;
		i++;
	}
	return false;
}

void printTheList(dataNode** headRef) {
	while ((*headRef) != nullptr) {
		std::cout << (*headRef)->value << std::endl;
		headRef = &(*headRef)->next;
	}
}

void clearList(dataNode **headRef) {
	dataNode* ptrToDelete;
	while ((*headRef) != nullptr)
	{
		ptrToDelete = (*headRef);
		*headRef = (*headRef)->next;
		delete ptrToDelete;
	}

}

// mi è venuta un idea