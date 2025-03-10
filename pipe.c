/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:54:59 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/04 21:18:05 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int p1[2];
	if (pipe(p1) == -1)
		return (-1);
	int pid = fork();
	if (pid == -1)
		return(-1);
	if (pid == 0)
	{
		int x;
		read(p1[0], &x, sizeof(x));
		printf("receveid %d\n", x);
		x = x *4;
		write(p1[1], &x, sizeof(x));
		printf("wrote1 %d\n", x);
		
	}
	else
	{
		srand(time(NULL));
		int y = rand() % 10;
		write(p1[1], &y, sizeof(y));
		//printf("wrote2 %d\n", y);
		read(p1[0], &y, sizeof(y));
		printf("result = %d\n", y);
		wait(NULL);
	}
	close(p1[0]);
	close(p1[1]);
	return(0);
}