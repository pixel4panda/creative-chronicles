// Assuming node structure as
typedef struct dllist
{
	VALUE val;
  	struct dllist *previous;
	struct dllist *next;
}
dllnode;

// Create a node, where a list doesn't yet exist
dllnode* create(VALUE xx)
{
  sllnode *temp = malloc(sizeof(dllnode);
  if (temp == NULL)
  {
	  return 1;
  }

  temp->val = xx;
  temp->previous = NULL;                        
  temp->next = NULL;

  return temp;
}

// Search through a linked list to find an element
bool find (dllnode *head, VALUE xx)
{
  for (dllnode *traverse = head; traverse != NULL; traverse = traverse->next)
  {
	  if (traverse->val == xx)
	  {
		  return true;
	  }
  }
return false;
}

// Insert a node at the beginning of the list
dllnode* add_to_list(dllnode *head, VALUE xx)
{
  sllnode *new = malloc(sizeofdllnode);
  if (new == NULL)
  {
	  return 1
  }

  // Populate new node with values
  new->val = xx;
  new->previous = NULL;
  new->next = head;

  // Previous start node has to backwards point to the node I am creating
  head->previous = new;

  // Make the node I am creating the start of the list
  head = new;

  return head;
}

// Free a single element from the list
void delete(dllnode *target)
{
  // If this is the beginning of the list
  if (target->previous == NULL)
  {
    target->next->previous = NULL;
  }

  // If this is the end of the list
  else if (target->next == NULL)
  {
    target->previous->next = NULL;
  }

  else 
  {  
    target->next->previous = target->previous;
    target->previous->next = target->next;
  }

  free(target);

  return;
}                      
                         
// Free an entire list
void destroy(dllnode *head)
{
	dllnode *node = head;
	while (node != NULL)
	{
		node = head->next;
		free(head);
		head = node;
	}
	return;
}
