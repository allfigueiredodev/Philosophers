#include "philosophers.h"

int	dc_lstsize(t_dclist *lst)
{
	int			total;
	t_dclist	*head;

	total = 0;
	if (!lst)
		return (total);
	head = lst;
	lst = lst->next;
	if (lst == head)
		return (1);
	else if (!lst || !lst->next)
		return (total);
	while (lst != head)
	{
		total++;
		lst = lst->next;
	}
	total++;
	lst = head;
	return (total);
}

t_dclist	*dc_lst_last(t_dclist *lst)
{
	t_dclist	*head;

	if (!lst)
		return (NULL);
	if (dc_lstsize(lst) == 1)
		return (lst);
	head = lst;
	lst = lst->next;
	while (lst->next != head)
		lst = lst->next;
	return (lst);
}

void	lst_prev_next(t_dclist **alst, t_dclist *new)
{
	t_dclist	*head;

	head = *(alst);
	if (alst)
	{
		if (dc_lstsize(*alst) == 0)
			*alst = new;
		else if (head->next == head)
		{
			new->prev = dc_lst_last(*(alst));
			new->next = head;
			head->next = new;
			head->prev = new;
		}
		else
		{
			new->prev = dc_lst_last(*(alst));
			new->prev->next = new;
			new->next = head;
			head->prev = new;
		}
	}
}
t_dclist	*lst_new_node(int id)
{
	t_dclist	*node;

	node = (t_dclist *)malloc(sizeof(t_dclist));
	if (!node)
		return (NULL);
	node->philo.philo_id = id;
	node->philo.left_fork_id = id;
	node->prev = node;
	node->next = node;
	return (&*node);
}