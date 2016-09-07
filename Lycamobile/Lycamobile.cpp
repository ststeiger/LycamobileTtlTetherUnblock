
#ifdef __cplusplus
	#include <cstdio>
	#include <cstdlib>
	
	#include <iostream>
	#include <fstream> // http://www.cprogramming.com/tutorial/lesson10.html
	// http://stackoverflow.com/questions/7868936/read-file-line-by-line
	#include <stdexcept>  // for std::runtime_error http://en.cppreference.com/w/cpp/error/runtime_error
	#include <string>
#else
	#include <stdio.h>
	#include <stdlib.h>
#endif

#define PROCFS_IPV4_TTL "/proc/sys/net/ipv4/ip_default_ttl"


#ifdef __cplusplus

	void PrintDefaultTtl(const char* szOldNew)
	{
		std::cout << szOldNew << " TTL: ";

		std::string content;
		std::ifstream file(PROCFS_IPV4_TTL);
		if (!file.is_open())
			throw std::runtime_error("Huh, couldn't open  "PROCFS_IPV4_TTL" ... ");

		while (file >> content)
		{
			std::cout << content << ' ';
		}

		file.close();
	}


	void SetDefaultTtl()
	{
		std::ofstream file(PROCFS_IPV4_TTL);
		if (!file.is_open())
			throw std::runtime_error("Huh, couldn't open  "PROCFS_IPV4_TTL" ... ");
		file << 85;
		file.close();
	}
#else 

	void PrintDefaultTtl(const char* szOldNew)
	{
		printf("%s TTL: ", szOldNew);

		int c;
		FILE *file;
		file = fopen(PROCFS_IPV4_TTL, "r");
		if (file)
		{
			while ((c = getc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
	}


	void SetDefaultTtl()
	{
		int val = 85;

		PrintDefaultTtl("Old");

		//FILE *f = fopen("/sys/class/backlight/acpi_video0/brightness", "w");
		FILE *f = fopen(PROCFS_IPV4_TTL, "w");

		if (!f)
		{
			fprintf(stderr, "Huh, couldn't open  "PROCFS_IPV4_TTL" ... ");
			exit(1);
		}
		fprintf(f, "%d", val);
		fclose(f);

		PrintDefaultTtl("New");
	}

#endif


int main(int argc, char* argv[])
{
	SetDefaultTtl();
	return 0;
}
