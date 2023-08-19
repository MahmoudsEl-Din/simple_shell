#include "simple_shell.h"


/**
 * createPathList - creates a linked list of directories in the PATH.
 * @env: the environment variable.
 * pointer to the new list.
 */
list_t *createPathList(char **env)
{
	list_t *head = NULL;
	char **environ;
	int len, i;

	len = 0;
	while (env[len])
		len++;
	environ = malloc(sizeof(char *) * len);
	if (!environ)
	{
		perror("MALLOC");
		return (NULL);
	}

	i = 0;
	while (env[i])
	{
		environ[i] = str_dup(env[i]);
		i++;
	}

	head = createList(environ);

	i = 0;
	while (i < len)
	{
		free(environ[i]);
		i++;
	}
	free(environ);

	return (head);
}


/**
 * addNodeToList - Add a new node to the list.
 * @head: pointer to the list.
 * @dir: some string to be placed in the new node.
 * pointer to the list.
 */
list_t *addNodeToList(list_t **head, char *dir)
{
	list_t *new, *port = *head;

	new = malloc(sizeof(list_t));
	if (new == NULL)
	{
		perror("ERROR: unable to allocate memory!!\n");
		return (NULL);
	}
	new->dir = dir;
	new->next = NULL;

	if (port)
	{
		while (port->next)
			port = port->next;
		port->next = new;
	}
	else
		*head = new;

	return new;
}


/**
 * createList - ccreate a list of directories in the PATH.
 * @environ: the environment variable.
 * pointer to the new list.
 */
list_t *createList(char **environ)
{
	list_t *head = NULL, *temp = NULL;
	char *dir, *port, *variableName, *variableValue = NULL;
	int i;

	i = 0;
	while (environ[i])
	{
		variableName = strtok(environ[i], "=");
		if (str_comp(variableName, "PATH") == 0)
		{
			variableValue = strtok(NULL, "\n");
			break;
		}
		i++;
	}
    
	/*if (variableValue)
	{
		port = strtok(variableValue, ":");
		while (port)
		{
			dir = str_dup(port);
			if (dir)
			{
				if (head == NULL)
				{
					head = addList(&head, dir);
					temp = head;
				}
				else
				{
					temp->next = addList(&temp->next, dir);
					temp = temp->next;
				}
				port = strtok(NULL, ":");
			}
			else
			{
				perror("ERROR: Failed to duplicate directory");
				break;
			}
		}
	} */

	if (variableValue)
	{
		i = 0;
		port = strtok(variableValue, ":");
		if (port)
		{
			dir = str_dup(port);
			head = addNodeToList(&head, dir);
			port = strtok(NULL, ":");
		}
		temp = head;
		while (port)
		{
			i++;
			dir = str_dup(port);
			addNodeToList(&head, dir);
			temp = temp->next;
			port = strtok(NULL, ":");
		}
	}
	else
		perror("ERROR: PATH environment variable not found\n");

	return head;
}




/**
 * freeDirList - free the list of directoriess.
 * @head: pinter to the list.
 */
void freeDirList(list_t *head)
{
	list_t *currentNode;
	list_t *nextNode;

	if (head)
	{
		currentNode = head;
		nextNode = head->next;


		while (nextNode)
		{
			free(currentNode->dir);
			free(currentNode);
			currentNode = nextNode;
			nextNode = nextNode->next;
		}
		free(currentNode->dir);
		free(currentNode);
	}
}

