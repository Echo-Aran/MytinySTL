#include"map.h"
#include"set.h"

int main()
{
	mystl::Map<const int, int> m;
	

	m.Insert(make_pair(3, 3));
	m.Insert(make_pair(1, 1));
	m.Insert(make_pair(2, 2));
	m.Insert(make_pair(7, 3));
	m.Insert(make_pair(8, 5));
	m.Insert(make_pair(4, 6));

	auto mit = m.begin();
	while (mit != m.end())
	{
		cout << mit->first << ":" << mit->second << endl;
		++mit;
	}
	cout << endl;


	mystl::Set<int> s;
	s.Insert(3);
	s.Insert(1);
	s.Insert(6);
	s.Insert(5);
	s.Insert(9);
	s.Insert(4);

	//��ͨ������Ե���const��Ȩ�޵���С�ǿ��Եģ�
	auto it = s.begin();
	while (it != s.end())
	{
		// ��Ӧ�������޸�key
		/*if (*it % 2 == 0)
		{
			*it += 10;
		}*/

		cout << *it << " ";
		++it;
	}
	cout << endl;

	/*for (auto& e : s)
	{
		cout << e << " ";
		
	}
	cout << endl; */



	return 0;
}