#include <iostream> 
#include <vector> 
#include <fstream> 

struct catcher {
	int x;
	int y;
};

std::vector <int> make_xod(int &pole_size, int &x, int &y, std::vector <catcher> &cat_coord, int &run_x, int &run_y) {
	std::vector <int> rez;
	std::vector <std::vector <int> > v(pole_size, std::vector <int>(pole_size));
	for (int i = 0; i < pole_size; i++) {
		for (int j = 0; j < pole_size; j++) {
			v[i][j] = 0;
		}
	}
	if (run_x != -1 && run_y != -1) {
		v[run_x][run_y] = 2;
	}
	for (int i = 0; i < cat_coord.size(); i++) {
		v[cat_coord[i].x][cat_coord[i].y] = 1;
	}
	//проверка на доступность соседних 
	int up = 0;
	int down = 0;
	int right = 0;
	int left = 0;
	if (y - 1 < 0 || v[x][y - 1] == 1) {
		up = -1;
	}
	if (y + 1 > pole_size - 1 || v[x][y + 1] == 1) {
		down = -1;
	}
	if (x - 1 < 0 || v[x - 1][y] == 1) {
		left = -1;
	}
	if (x + 1 > pole_size - 1 || v[x + 1][y] == 1) {
		right = -1;
	}
	//проверка на моментальную победу 
	if (up != -1 && v[x][y - 1] == 2) {
		rez.push_back(0);
		rez.push_back(-1);
		return rez;
	}
	if (down != -1 && v[x][y + 1] == 2) {
		rez.push_back(0);
		rez.push_back(1);
		return rez;
	}
	if (left != -1 && v[x - 1][y] == 2) {
		rez.push_back(-1);
		rez.push_back(0);
		return rez;
	}
	if (right != -1 && v[x + 1][y] == 2) {
		rez.push_back(1);
		rez.push_back(0);
		return rez;
	}
	//расстановка приоритетов 
	if (right != -1 && x < run_x) {
		right += 100;
		if (y == run_y) {
			right += 100;
		}
	}
	if (left != -1 && x > run_x) {
		left += 100;
		if (y == run_y) {
			left += 100;
		}
	}
	if (down != -1 && y < run_y) {
		down += 100;
		if (x == run_x) {
			down += 100;
		}
	}
	if (up != -1 && x > run_x) {
		up += 100;
		if (y == run_y) {
			up += 100;
		}
	}
	for (int i = 0; i < cat_coord.size(); i++) {
		if (right != -1 && x <= cat_coord[i].x) {
			right -= 1;
		}
		if (left != -1 && x >= cat_coord[i].x) {
			left -= 1;
		}
		if (down != -1 && y <= cat_coord[i].y) {
			down -= 1;
		}
		if (up != -1 && y >= cat_coord[i].y) {
			up -= 1;
		}
	}
	if (up >= down && up >= right && up >= left) {
		rez.push_back(0);
		rez.push_back(-1);
		return rez;
	}
	if (down >= up && down >= right && down >= left) {
		rez.push_back(0);
		rez.push_back(1);
		return rez;
	}
	if (right >= down && right >= up && right >= left) {
		rez.push_back(1);
		rez.push_back(0);
		return rez;
	}
	if (left >= down && left >= right && left >= left) {
		rez.push_back(0);
		rez.push_back(-1);
		return rez;
	}
}

int main(int argc, char *argv[]) {
	//////////////INIT///////////////////////////////////////////////////////////////////////////////////////////// 
	std::ifstream fin(argv[1]);
	int role, pole_type, pole_size, num_catchers, runner_long, xodmax, numxod, run_x, run_y;
	fin » role » pole_type » pole_size » num_catchers » runner_long » xodmax » numxod » run_x » run_y;
	std::vector <catcher> cat_coord(num_catchers);
	for (int i = 0; i < num_catchers; i++) {
		fin » cat_coord[i].x;
		fin » cat_coord[i].y;
	}
	fin.close();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	std::ofstream fout(argv[2]);
	if (role == 0 && numxod == 0) {
		std::vector <std::vector <int> > v(pole_size, std::vector <int>(pole_size));
		for (int i = 0; i < pole_size; i++) {
			for (int j = 0; j < pole_size; j++) {
				v[i][j] = 0;
			}
		}
		for (int i = 0; i < num_catchers; i++) {
			int x = rand() % pole_size;
			int y = rand() % pole_size;
			while (v[x][y] == 1) {
				x = rand() % pole_size;
				y = rand() % pole_size;
			}
			fout « x « " " « y « std::endl;
		}
		fout.close();
		return 0;
	}
	for (int i = 0; i < num_catchers; i++) {
		std::vector <int> tmp = make_xod(pole_size, cat_coord[i].x, cat_coord[i].y, cat_coord, run_x, run_y);
		fout « tmp[0] « " " « tmp[1] « std::endl;
	}
	fout.close();
	return 0;
}