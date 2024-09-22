// LIstTool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
	std::wcout.imbue(std::locale("chs")); // 设置locale为简体中文
	if (argc < 2)
	{
		MessageBox(0, L"请把文件拖到exe",0,0);
		return 1;
	}
	
    const char* filename = argv[1];
    std::ifstream file(filename, std::ios::binary);

    // 确保文件打开
    if (!file) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return 1;
    }

    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // 读取文件内容到string
    std::string binary_data(size, '\0');
    if (file.read(binary_data.data(), size)) {
        // 成功读取文件内容到binary_data
        // 使用binary_data...
        //std::cerr << binary_data << std::endl;
    }
    else {
        // 读取失败
        std::cerr << "无法读取文件内容" << std::endl;
    }

    std::vector<std::string> listcontext;
    int j = 0;
    for (size_t i = 0; i < binary_data.length() + 1; i++)
    {
        //std::cout << binary_data.c_str() + i << "\n";
        if (memcmp(binary_data.c_str() + i, "\r\n",2) == 0 || memcmp(binary_data.c_str() + i, "", 1) == 0) {
            listcontext.push_back(binary_data.substr(j, i -j));
            std::cout << binary_data.substr(j, i - j) << "\n";
            j = i + 2;        
        }
    }
    if (!listcontext.empty())
    {       
        std::string outyolov8c;
        for (size_t i = 0; i < listcontext.size(); i++)
        {    
            outyolov8c += " " + std::to_string(i) + ": " + listcontext[i] + "\r\n"; 
        }

        std::string outxlable;
        for (size_t i = 0; i < listcontext.size(); i++)
        {
            outxlable += " - " + listcontext[i] + "\r\n";
        }      

        std::string outcname;
        for (size_t i = 0; i < listcontext.size(); i++)
        {
           
            if ((i + 1) % 10 == 0)
            {
                outcname += "\"" + listcontext[i] + "\",\n";
            }
            else
            {
                outcname += "\"" + listcontext[i] + "\",";
            }
        }
        outcname = outcname.substr(0, outcname.find_last_of(','));
        outcname += "\n";
        for (size_t i = 0; i < listcontext.size(); i++)
        {

            if ((i + 1) % 10 == 0)
            {
                outcname += "xorstr_(\"" + listcontext[i] + "\"),\n";
            }
            else
            {
                outcname += "xorstr_(\"" + listcontext[i] + "\"),";
            }
        }
        outcname = outcname.substr(0, outcname.find_last_of(','));

        outcname += "\n";
        for (size_t i = 0; i < listcontext.size(); i++)
        {
            outcname += "#define  index_" + listcontext[i] + "       "+ std::to_string(i) + " \n";
        }

        std::string in_t = filename;// argv[1];
        std::string out_yolov8 = in_t.substr(0, in_t.find_last_of('.')) + "_yv8.yaml";
        std::string out_xl = in_t.substr(0, in_t.find_last_of('.')) + "_xl.yaml";
        std::string out_cname = in_t.substr(0, in_t.find_last_of('.')) + "_name.c";
        std::cout << out_yolov8 << "\n";
        std::cout << out_xl << "\n";
        std::cout << out_cname << "\n";
        std::ofstream ofs(out_yolov8, std::ios::out | std::ios::binary);
        ofs.write(outyolov8c.data(), outyolov8c.size());
        ofs.close();

        std::ofstream ofss(out_xl, std::ios::out | std::ios::binary);
        ofss.write(outxlable.data(), outxlable.size());
        ofss.close();
        //std::cout << outcname << "\n";
        std::ofstream ofsss(out_cname, std::ios::out | std::ios::binary);
        ofsss.write(outcname.data(), outcname.size());
        ofsss.close();
    }
	getchar();
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
