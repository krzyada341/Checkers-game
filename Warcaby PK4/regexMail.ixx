export module regexMail;
import <iostream>;
import <regex>;

export bool sprawdz(std::string& email)
{
	std::regex regex_mail("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return std::regex_match(email, regex_mail);
}