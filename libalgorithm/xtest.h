#ifndef _XTEST_
#define _XTEST_

#define EXPECT_EQ(lcond, rcond) do {\
	if ((lcond) == (rcond)) {\
		printf("PASS! <FILE:%s LINE:%d>\n", __FILE__, __LINE__);\
	} else {\
		printf("FAILED! <FILE:%s LINE:%d>\n", __FILE__, __LINE__);\
	}\
} while (0)

#endif