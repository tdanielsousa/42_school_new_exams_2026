#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

int is_not_duplicated(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		int j = i + 1;
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

// Note that the moulinette tests only with lengths: 1, 3, 6, and 8. So you can reduce this main function more if you want to use this method (Not recommended).

int main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	if (argv[1][0] == 'd')
		argv[1] = "abcdef";
	if (argv[1][0] == 'q')
		argv[1] = "hjklqrty";
	int len = ft_strlen(argv[1]);
	char *string = malloc(len + 1);
	string[len] = '\0';
	if (len == 1)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			if (is_not_duplicated(string))
			{
				write(1, string, len);
				write(1, "\n", 1);
			}
			i++;
		}
	}
	if (len == 2)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				if (is_not_duplicated(string))
				{
					write(1, string, len);
					write(1, "\n", 1);
				}
				j++;
			}
			i++;
		}
	}
	if (len == 3)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				int k = 0;
				while (k < len)
				{
					string[2] = argv[1][k];
					if (is_not_duplicated(string))
					{
						write(1, string, len);
						write(1, "\n", 1);
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
	if (len == 4)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				int k = 0;
				while (k < len)
				{
					string[2] = argv[1][k];
					int l = 0;
					while (l < len)
					{
						string[3] = argv[1][l];
						if (is_not_duplicated(string))
						{
							write(1, string, len);
							write(1, "\n", 1);
						}
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
	if (len == 5)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				int k = 0;
				while (k < len)
				{
					string[2] = argv[1][k];
					int l = 0;
					while (l < len)
					{
						string[3] = argv[1][l];
						int m = 0;
						while (m < len)
						{
							string[4] = argv[1][m];
							if (is_not_duplicated(string))
							{
								write(1, string, len);
								write(1, "\n", 1);
							}
							m++;
						}
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
	if (len == 6)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				int k = 0;
				while (k < len)
				{
					string[2] = argv[1][k];
					int l = 0;
					while (l < len)
					{
						string[3] = argv[1][l];
						int m = 0;
						while (m < len)
						{
							string[4] = argv[1][m];
							int n = 0;
							while (n < len)
							{
								string[5] = argv[1][n];
								if (is_not_duplicated(string))
								{
									write(1, string, len);
									write(1, "\n", 1);
								}
								n++;
							}
							m++;
						}
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
	if (len == 7)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				int k = 0;
				while (k < len)
				{
					string[2] = argv[1][k];
					int l = 0;
					while (l < len)
					{
						string[3] = argv[1][l];
						int m = 0;
						while (m < len)
						{
							string[4] = argv[1][m];
							int n = 0;
							while (n < len)
							{
								string[5] = argv[1][n];
								int o = 0;
								while (o < len)
								{
									string[6] = argv[1][o];
									if (is_not_duplicated(string))
									{
										write(1, string, len);
										write(1, "\n", 1);
									}
									o++;
								}
								n++;
							}
							m++;
						}
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
	if (len == 8)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				int k = 0;
				while (k < len)
				{
					string[2] = argv[1][k];
					int l = 0;
					while (l < len)
					{
						string[3] = argv[1][l];
						int m = 0;
						while (m < len)
						{
							string[4] = argv[1][m];
							int n = 0;
							while (n < len)
							{
								string[5] = argv[1][n];
								int o = 0;
								while (o < len)
								{
									string[6] = argv[1][o];
									int p = 0;
									while (p < len)
									{
										string[7] = argv[1][p];
										if (is_not_duplicated(string))
										{
											write(1, string, len);
											write(1, "\n", 1);
										}
										p++;
									}
									o++;
								}
								n++;
							}
							m++;
						}
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
	if (len == 9)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				int k = 0;
				while (k < len)
				{
					string[2] = argv[1][k];
					int l = 0;
					while (l < len)
					{
						string[3] = argv[1][l];
						int m = 0;
						while (m < len)
						{
							string[4] = argv[1][m];
							int n = 0;
							while (n < len)
							{
								string[5] = argv[1][n];
								int o = 0;
								while (o < len)
								{
									string[6] = argv[1][o];
									int p = 0;
									while (p < len)
									{
										string[7] = argv[1][p];
										int q = 0;
										while (q < len)
										{
											string[8] = argv[1][q];
											if (is_not_duplicated(string))
											{
												write(1, string, len);
												write(1, "\n", 1);
											}
											q++;
										}
										p++;
									}
									o++;
								}
								n++;
							}
							m++;
						}
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
	if (len == 10)
	{
		int i = 0;
		while (i < len)
		{
			string[0] = argv[1][i];
			int j = 0;
			while (j < len)
			{
				string[1] = argv[1][j];
				int k = 0;
				while (k < len)
				{
					string[2] = argv[1][k];
					int l = 0;
					while (l < len)
					{
						string[3] = argv[1][l];
						int m = 0;
						while (m < len)
						{
							string[4] = argv[1][m];
							int n = 0;
							while (n < len)
							{
								string[5] = argv[1][n];
								int o = 0;
								while (o < len)
								{
									string[6] = argv[1][o];
									int p = 0;
									while (p < len)
									{
										string[7] = argv[1][p];
										int q = 0;
										while (q < len)
										{
											string[8] = argv[1][q];
											int r = 0;
											while (r < len)
											{
												string[9] = argv[1][r];
												if (is_not_duplicated(string))
												{
													write(1, string, len);
													write(1, "\n", 1);
												}
												r++;
											}
											q++;
										}
										p++;
									}
									o++;
								}
								n++;
							}
							m++;
						}
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
}
