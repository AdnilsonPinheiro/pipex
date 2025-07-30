/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:24:07 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/30 18:08:36 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*joins res to buffer freeing the temp
basically a strjoin with memory security*/
char	*ft_free_join(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	free(stash);
	return (temp);
}
