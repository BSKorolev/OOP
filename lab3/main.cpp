#include <iostream>
#include <vector>

class Array3d {
private:
    std::vector<int> data;
    int dim0, dim1, dim2;

public:
    Array3d(int dim0, int dim1, int dim2) : dim0(dim0), dim1(dim1), dim2(dim2) {
        data.resize(dim0 * dim1 * dim2);
    }

    int& operator()(int i, int j, int k) {
        return data[i * dim1 * dim2 + j * dim2 + k];
    }

    std::vector<int> GetValues0(int i) {
        std::vector<int> values;
        for (int j = 0; j < dim1; ++j) {
            for (int k = 0; k < dim2; ++k) {
                values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
            }
        }
        return values;
    }

    std::vector<int> GetValues1(int j) {
        std::vector<int> values;
        for (int i = 0; i < dim0; ++i) {
            for (int k = 0; k < dim2; ++k) {
                values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
            }
        }
        return values;
    }

    std::vector<int> GetValues2(int k) {
        std::vector<int> values;
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
            }
        }
        return values;
    }

    std::vector<int> GetValues01(int i, int j) {
        std::vector<int> values;
        for (int k = 0; k < dim2; ++k) {
            values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
        }
        return values;
    }

    std::vector<int> GetValues02(int i, int k) {
        std::vector<int> values;
        for (int j = 0; j < dim1; ++j) {
            values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
        }
        return values;
    }

    std::vector<int> GetValues12(int j, int k) {
        std::vector<int> values;
        for (int i = 0; i < dim0; ++i) {
            values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
        }
        return values;
    }

    void SetValues0(int i, std::vector<int> values) {
        for (int j = 0; j < dim1; ++j) {
            for (int k = 0; k < dim2; ++k) {
                data[i * dim1 * dim2 + j * dim2 + k] = values[j * dim2 + k];
            }
        }
    }

    void SetValues1(int j, std::vector<int> values) {
        for (int i = 0; i < dim0; ++i) {
            for (int k = 0; k < dim2; ++k) {
                data[i * dim1 * dim2 + j * dim2 + k] = values[i * dim2 + k];
            }
        }
    }

    void SetValues2(int k, std::vector<int> values) {
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                data[i * dim1 * dim2 + j * dim2 + k] = values[i * dim1 + j];
            }
        }
    }

    void SetValues01(int i, int j, std::vector<int> values) {
        for (int k = 0; k < dim2; ++k) {
            data[i * dim1 * dim2 + j * dim2 + k] = values[k];
        }
    }

    void SetValues02(int i, int k, std::vector<int> values) {
        for (int j = 0; j < dim1; ++j) {
            data[i * dim1 * dim2 + j * dim2 + k] = values[j];
        }
    }

    void SetValues12(int j, int k, std::vector<int> values) {
        for (int i = 0; i < dim0; ++i) {
            data[i * dim1 * dim2 + j * dim2 + k] = values[i];
        }
    }

    static Array3d ones(int dim0, int dim1, int dim2) {
        Array3d array(dim0, dim1, dim2);
        for (int i = 0; i < dim0 * dim1 * dim2; ++i) {
            array.data[i] = 1;
        }
        return array;
    }

    static Array3d zeros(int dim0, int dim1, int dim2) {
        Array3d array(dim0, dim1, dim2);
        for (int i = 0; i < dim0 * dim1 * dim2; ++i) {
            array.data[i] = 0;
        }
        return array;
    }

    static Array3d fill(int dim0, int dim1, int dim2, int value) {
        Array3d array(dim0, dim1, dim2);
        for (int i = 0; i < dim0 * dim1 * dim2; ++i) {
            array.data[i] = value;
        }
        return array;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Array3d arr(3, 3, 3);

    arr(1, 1, 1) = 7;
    std::cout << "The value in (1, 1, 1): " << arr(1, 1, 1) << std::endl;

    auto values1 = arr.GetValues1(1);
    std::cout << "Values for j=1: ";
    for (int val : values1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    auto values01 = arr.GetValues01(1, 1);
    std::cout << "Values for i=1, j=1: ";
    for (int val : values01) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    arr.SetValues01(1, 1, { 10, 11, 12 });
    auto updatedValues01 = arr.GetValues01(1, 1);
    std::cout << "Changed values for i=1, j=1: ";
    for (int val : updatedValues01) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    auto onesArray = Array3d::ones(2, 2, 2);
    auto zerosArray = Array3d::zeros(2, 2, 2);
    auto fillArray = Array3d::fill(2, 2, 2, 7);

    std::cout << "array of ones:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                std::cout << onesArray(i, j, k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "array of zeros:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                std::cout << zerosArray(i, j, k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "array of 7:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                std::cout << fillArray(i, j, k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}