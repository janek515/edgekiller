#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <regex>
#include <nlohmann/json.hpp>
#include <sstream>
#include <format>
#include <pathcch.h>


using json = nlohmann::json;
using namespace std;


string UrlDecode(const string& value)
{
    string result;
    result.reserve(value.size());
    
    for (size_t i = 0; i < value.size(); ++i)
    {
        char ch = value[i];
        
        if (ch == '%' && (i + 2) < value.size())
        {
            string hex = value.substr(i + 1, 2);
            char dec = static_cast<char>(strtol(hex.c_str(), nullptr, 16));
            result.push_back(dec);
            i += 2;
        }
        else
        {
            result.push_back(ch);
        }
    }
    
    return result;
}

void OpenBrowser(bool isUrl = false, string url = ""){
    char pathBuffer[MAX_PATH];
    GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
    std::string path(pathBuffer);
    path = path.substr(0, path.length() - 14);

    ifstream i(path + "config.json");
    stringstream buffer;
    buffer << i.rdbuf();
    json j = json::parse(buffer.str());
    string preffered_browser_path = j.at("preffered_browser_path");
    if(!isUrl){
        ShellExecute(NULL, "open", preffered_browser_path.c_str(), NULL, NULL, SW_SHOWNORMAL);
        return;
    }
    string preffered_search_engine = j.at("preffered_search_engine");
    string finalUrl;
    auto q = url.find("?q=");
    auto end = url.find("&");
    if(q != string::npos){
        string query = url.substr(q + 3, (end == string::npos ? string::npos : end - q - 3));
        finalUrl = format(preffered_search_engine, query);
    }
    else {
        finalUrl = url;
    }
    ShellExecute(NULL, "open", preffered_browser_path.c_str(), finalUrl.c_str(), NULL, SW_SHOWNORMAL);
}



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    // OpenBrowser(true, "https://www.bing.com/search?q=fgjfghfg&form=WSBEDG&qs=SW&cvid=5d845c7c48f740e2b604109b785b0ff6&pq=fgjfghfg&cc=PL&setlang=pl-PL&nclid=95A69412FE8EA0A0EA3BEC1D4A03F4AD&ts=1637790945412&nclidts=1637790945&tsms=412&wsso=Moderate");
    int argc;
    wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    if (argc < 4){
        cout << "No args" << endl;
        OpenBrowser();
        return 0;
    }
    wstring w_url(argv[3]);
    wcout << w_url << endl;
    std::string url(w_url.length(), 0);
    std::transform(w_url.begin(), w_url.end(), url.begin(), [] (wchar_t c) {
        return (char)c;
    });
    // todo: check if url is valid
    if(!url.starts_with("microsoft-edge:")){
        OpenBrowser();
        return 0;
    }
    url = url.substr(15);
    if(url.rfind("?", 0) == 0){
        smatch match_result;
        regex r("&url");
        string source = url.substr(1);
        if(!regex_search(source, match_result, r)){
            cout << "Invalid URI" << endl;
            return 1;
        }
        url = UrlDecode(url.substr(match_result.position()+6));
        cout << url << endl;
        OpenBrowser(true, url);
        return 0;
    }
    OpenBrowser(true, url);
    return 0;
}
