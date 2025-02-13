// Assuming node structure as
typedef struct sllist
{
	VALUE val;
	struct sllist *next;
}
sllnode;

// Create a node, where a list doesn't yet exist
sllnode* create(VALUE xx)
{
  sllnode *temp = malloc(sizeof(sllnode);
  if (temp == NULL)
  {
	  return 1;
  }

  temp->val = xx;
  temp->next = NULL;

  return temp;
}

// Search through a linked list to find an element
bool find (sllnode *head, VALUE xx)
{
  for (sllnode *traverse = head; traverse != NULL; traverse = traverse->next)
  {
	  if (traverse->val == xx)
	  {
		  return true;
	  }
  }
return false;
}

// Insert a node at the beginning of the list
sllnode* add_to_list(sllnode *head, VALUE xx)
{
  sllnode *new = malloc(sizeofsllnode);
  if (new == NULL)
  {
	  return 1
  }

  new->val = xx;
  new->next = head;

  head = new;

  return head;
}

// Free an entire list
void destroy(sllnode *head)
{
	sllnode *node = head;
	if ( node->next == NULL)
	{
		free(node);
		return;
	}
	destroy(node->next);
}


