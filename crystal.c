#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void crystal(double reach, double threshold)
{
	double res = 0;
	int m, d, div;
	for (m = 1; m <= 64; ++m) {
		for (d = 1; d <= 52; ++d) {
			for (div = 1; div <= 128; ++div) {
				res = 100000000.0 / 1.0 * m / d;
				if (res < 400000000.0 || res > 1440000000.0)
					continue;
				res = 100000000.0 / 1.0 * m / d / div;
				if (res < (reach-threshold) || res > (reach+threshold))
					continue;
				double diff;
				if (res > reach)
					diff = res - reach;
				else
					diff = reach - res;
				if (diff > threshold)
					continue;
				printf("100M * %d / %d / %d = %f, 相差: %f\n", m, d, div, res, diff);
			}
		}
	}
}

extern char *optarg;

void usage(char **argv)
{
	printf("Usage: %s [-o frequency] [-t threshold] [-h help]\n", argv[0]);
	exit(1);
}

int main(int argc, char **argv)
{
	const struct option longOpts[] = {
		{"out", required_argument, NULL, 'o'},
		{"thr", required_argument, NULL, 't'},
		{"help", no_argument, NULL, 'h'},
		{NULL, no_argument, NULL, 0}
	};

	int longIndex;
	int opt;
	double reach, threshold;
	static const char *opts = "o:t:h";

	if (argc < 2)
		usage(argv);

	while ((opt = getopt_long(argc, argv, opts, (const struct option*)&longOpts, &longIndex)) != -1) {
		switch (opt) {
			case 'o':
				reach = atof(optarg);
				break;
			case 't':
				threshold = atof(optarg);
				break;
			case 'h':
				usage(argv);
				break;
			case 0:
				printf("ohoh\n");
				break;
		}
	}

	printf("reach: %f, threshold: %f\n", reach, threshold);

	crystal(reach, threshold);
	return 0;
}

