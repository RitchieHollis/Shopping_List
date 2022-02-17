/* AbstractFactoryExample.cpp : This file contains the 'main' function.Program execution begins and ends there.

Abstract factory -> creational design pattern that lets you produce families of related objects without specifying their concrete classes.

The first thing the Abstract Factory pattern suggests is to explicitly declare interfaces for each distinct product of the product family (e.g., chair, sofa or coffee table). 
Then you can make all variants of products follow those interfaces. For example, all chair variants can implement the Chair interface; 
all coffee table variants can implement the CoffeeTable interface, and so on.

The next move is to declare the Abstract Factory—an interface with a list of creation methods for all products that are part of the product family 
(for example, createChair, createSofa and createCoffeeTable). These methods must return abstract product types represented by the interfaces we extracted previously: 
Chair, Sofa, CoffeeTable and so on.

Use when there's different types of objects/misc, depending of a choice done by user, OS etc.
*/

#include <iostream>
#include <set>
#include <algorithm>
#include <exception>

using list = std::set<std::string>;
                                                                                           
list shopList = {};

class Chair {

public:
    virtual ~Chair() {};
    virtual list AddToList(list&) const = 0;                                                                                           
};

class RetroChair : public Chair {

public:
    virtual list AddToList(list& shopList) const override {

        shopList.insert("Retro_Chair");
        return shopList;
    }
};

class ModernChair : public Chair {

public:
    virtual list AddToList(list& shopList) const override {

        shopList.insert("Modern_Chair");
        return shopList;
    }
};

class Table {

public:
    virtual ~Table() {};
    virtual list AddToList(list& a) const = 0;
};

class RetroTable : public Table {

public:
    virtual list AddToList(list& shopList) const override {

        shopList.insert("Retro_Table");
        return shopList;
    }
};

class ModernTable : public Table {

public:
    virtual list AddToList(list& shopList) const override {

        shopList.insert("Modern_Table");
        return shopList;
    }
};

class AbstractFactory {

public:
    virtual Table* CreateTable() const = 0;
    virtual Chair* CreateChair() const = 0;
};

class RetroFactory : public AbstractFactory {
public:
    Table* CreateTable() const override {
        return new RetroTable();
    }
    Chair* CreateChair() const override {
        return new RetroChair();
    }
};

class ModernFactory : public AbstractFactory {
public:
    Table* CreateTable() const override {
        return new ModernTable();
    }
    Chair* CreateChair() const override {
        return new ModernChair();
    }
};

void ClientCodeChair(const AbstractFactory& factory) {

    const Chair* product_a = factory.CreateChair();
    product_a->AddToList(shopList);
    delete product_a;
}

void ClientCodeTable(const AbstractFactory& factory) {

    const Table* product_a = factory.CreateTable();
    product_a->AddToList(shopList);
    delete product_a;
}

void printList(list& a) {

    std::cout << "///////////////////////\n";
    for (auto& i : a) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;
    std::cout << "///////////////////////\n";
}

void Adding() {

    std::cout << "What do you want to add\n";
    std::string choice;
    std::cin >> choice;
    std::transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

    if (choice == "RC") {
        RetroFactory* f1 = new RetroFactory();
        ClientCodeChair(*f1);
        delete f1;
    }
    else if (choice == "MC") {
        ModernFactory* f1 = new ModernFactory();
        ClientCodeChair(*f1);
        delete f1;
    }
    else if (choice == "RT") {
        RetroFactory* f1 = new RetroFactory();
        ClientCodeTable(*f1);
        delete f1;
    }
    else if (choice == "MT") {
        ModernFactory* f1 = new ModernFactory();
        ClientCodeTable(*f1);
        delete f1;
    }

    std::cout << "This is your shopping list: \n";
    printList(shopList);
}

void Remove(std::string a) {

    if (shopList.empty())
        throw "Shop List is empty";

    if (!(shopList.find(a) != shopList.end())) {
        std::string f = ("There's no " + a + " in shop list");
        throw f;
    }
    shopList.erase(a);
}

int main()
{
    char c = 'Y';
    do {
        std::cout << "Add/Remove/Show List? A/R/S\n";
        std::cin >> c;
        c = std::toupper(c);
        switch (c) {
            case 'A': Adding(); continue;
            case 'R': 
                try { 
                    std::string choice;
                    std::cin >> choice;
                    Remove(choice);
                    continue;
                }
                catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                    continue;
                }
                catch (std::string& e) {
                    std::cout << e << std::endl;
                    continue;
                }
            case 'S': printList(shopList); continue;
            default: std::cout << "I'm sorry, I don't understand\n"; continue;
        }
    } while (c == 'A'|| c == 'R'|| c == 'S');

    std::cout << "Final shopping list: \n";
    printList(shopList);

    return EXIT_SUCCESS;
}