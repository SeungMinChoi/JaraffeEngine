#pragma once

class GenericFile
{
public:
	GenericFile();
	virtual ~GenericFile();

public:
	static std::vector<char> ReadFile(const std::string& Filename);
};