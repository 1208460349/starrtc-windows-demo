#pragma once
#include <string>
using namespace std;

class IErrorCallback
{
public:
	/**
	 * ����
	 * @param errMsg
	 * @param data
	 */
	virtual void error(string errMsg) = 0;
};

