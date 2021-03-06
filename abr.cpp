//
//  Binary Search Tree
//
//  Copyright (c) 2017 Olivier Cuisenaire. All rights reserved.
//

// Chau Ying Kot, Teo Ferrari, Gildas Houlmann
// ASD1_B_J

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <queue>
#include <cassert>
#include <stdexcept>

using namespace std;

template<typename T>
class BinarySearchTree {
public:

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;

private:
    /**
     *  @brief Noeud de l'arbre.
     *
     * contient une cle et les liens vers les sous-arbres droit et gauche.
     */
    struct Node {
        const value_type key; // clé non modifiable
        Node* right;          // sous arbre avec des cles plus grandes
        Node* left;           // sous arbre avec des cles plus petites
        size_t nbElements;    // nombre de noeuds dans le sous arbre dont
        // ce noeud est la racine

        Node(const_reference key)  // seul constructeur disponible. key est obligatoire
                : key(key), right(nullptr), left(nullptr), nbElements(1) {
            cout << "(C" << key << ") ";
        }

        ~Node()               // destructeur
        {
            cout << "(D" << key << ") ";
        }

        Node() = delete;             // pas de construction par défaut
        Node(const Node&) = delete;  // pas de construction par copie
        Node(Node&&) = delete;       // pas de construction par déplacement
    };

    /**
     *  @brief  Racine de l'arbre. nullptr si l'arbre est vide
     */
    Node* _root;

public:
    /**
     *  @brief Constructeur par défaut. Construit un arbre vide
     *
     *  @remark O(1)
     */
    BinarySearchTree() : _root(nullptr) {
        /* ... */
    }

    /**
     *  @brief Constucteur de copie. Crée un arbre temporaire et copie l'arbre
     *  dans la valeur temp et si tout ce passe bien, on swap les deux racine
     *
     *  @param other le BinarySearchTree à copier
     *
     *  @remark O(n)
     *
     */
    BinarySearchTree(BinarySearchTree& other) : _root(nullptr) {
        BinarySearchTree temp;
        temp.copyTree(other._root);
        std::swap(temp._root, _root);
    }


private :
    /**
     * @brief Copie l'arbre l'arbre courant depuis le noeud donée
     *
     * @param node la racine de l'arbre où on commence à copier
     *
     * @remark O(n)
     */
    void copyTree(const Node* node) {
        if (node != nullptr) {
            insert(node->key);
            copyTree(node->left);
            copyTree(node->right);
        }
    }

public:
    /**
     *  @brief Opérateur d'affectation par copie. Crée un arbre temporaire et copie
     *  l'arbre dans la valeur temp et si tout ce passe bien, on swap les
     *  deux racine et retourne un pointer sur l'arbre
     *
     *  @param other le BinarySearchTree à copier
     *
     *  @remark O(n)
     *
     */
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        BinarySearchTree temp;
        temp.copyTree(other._root);
        std::swap(temp._root, _root);
        return *this;
    }

    /**
     *  @brief Echange le contenu avec un autre BST
     *  Swap les deux racines
     *
     *  @param other le BST avec lequel on echange le contenu
     *
     *  @remark O(1)
     *
     */
    void swap(BinarySearchTree& other) noexcept {
        std::swap(_root, other._root);
    }

    /**
     *  @brief constructeur de copie par déplacement, deplace les ressources de
     *  l'arbre passée en paramètre vers notre arbre courant.
     *  La racine de l'arbre passée en paramètre pointera sur un nullptr
     *
     *  @param other le BST dont on vole le contenu
     *
     *  @remark O(1)
     *
     */
    BinarySearchTree(BinarySearchTree&& other) noexcept : _root(move(other._root)) {
        other._root = nullptr;
    }

    /**
     *  @brief Opérateur d'affectation par déplacement, deplace les ressources de
     *  l'arbre passée en paramètre vers notre arbre courant.
     *  La racine de l'arbre passée en paramètre pointera sur un nullptr
     *  Il retourne un pointer sur l'arbre courant
     *
     *  @param other le BST dont on vole le contenu
     *
     *  @remark O(1)
     *
     */
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        _root = std::move(other._root);
        other._root = nullptr;
        return *this;
    }

    //
    // @brief Destructeur
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée deleteSubTree(Node*)
    //
    // @remark O(n)
    ~BinarySearchTree() {
        deleteSubTree(_root);
    }

private:
    //
    // @brief Fonction détruisant (delete) un sous arbre
    //
    // @param r la racine du sous arbre à détruire.
    //          peut éventuellement valoir nullptr
    //
    // @remark O(taille de l'arbre avec r comme racine)
    static void deleteSubTree(Node* r) noexcept {
        if (r != nullptr) { // Condition d'arrêt pour la résursvité
            if (r->left != nullptr) {
                deleteSubTree(r->left);
            }
            if (r->right != nullptr) {
                deleteSubTree(r->right);
            }

        }
        delete (r);
    }

public:
    //
    // @brief Insertion d'une cle dans l'arbre
    //
    // @param key la clé à insérer.
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée insert(Node*&,const_reference)
    //
    // @remark O(log(n))
    void insert(const_reference key) {
        insert(_root, key);
    }

private:
    //
    // @brief Insertion d'une cle dans un sous-arbre
    //
    // @param r la racine du sous-arbre dans lequel
    //          insérer la cle.
    // @param key la clé à insérer.
    //
    // @return vrai si la cle est inseree. faux si elle etait deja presente.
    //
    // Si la cle est deja presente, cette fonction ne fait rien.
    // x peut éventuellement valoir nullptr en entrée.
    // la fonction peut modifier x, reçu par référence, si nécessaire
    //
    // @remark O(log(n))
    static bool insert(Node*& r, const_reference key) {
        if (r == nullptr) { // Si la racine est nul on peut inserer directement
            r = new Node{key};
            r->nbElements = 1;
            return true;
        } else if (key < r->key) { // Si la clé est plus petite que la clé du
            // noeaud inserer à gauche
            bool inserted = insert(r->left, key);
            if (inserted) {
                if (r->right == nullptr) {
                    r->nbElements = (r->left->nbElements + 1);
                } else if (r->left == nullptr) {
                    r->nbElements = (r->right->nbElements + 1);
                } else {
                    r->nbElements = r->right->nbElements + r->left->nbElements + 1;
                }
            }
            return inserted;
        } else if (key > r->key) { // Si la clé est plus grande que la clé du
            // noeaud inserer à droite
            bool inserted = insert(r->right, key);
            if (inserted) {
                if (r->right == nullptr) {
                    r->nbElements = (r->left->nbElements + 1);
                } else if (r->left == nullptr) {
                    r->nbElements = (r->right->nbElements + 1);
                } else {
                    r->nbElements = r->right->nbElements + r->left->nbElements + 1;
                }
            }
            return inserted;
        } else {// La clé est déja présent
            return false;
        }
    }

public:
    //
    // @brief Recherche d'une cle.
    //
    // @param key la cle a rechercher
    //
    // @return vrai si la cle trouvee, faux sinon.
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée contains(Node*,const_reference)
    //
    // @remark O(log(n))
    bool contains(const_reference key) const noexcept {
        return contains(_root, key);
    }

private:
    //
    // @brief Recherche d'une cle dans un sous-arbre
    //
    // @param key la cle a rechercher
    // @param r   la racine du sous-arbre
    //
    // @return vrai si la cle trouvee, faux sinon.
    //
    // @remark  O(log(n))
    static bool contains(Node* r, const_reference key) noexcept {
        if (r == nullptr) { // Si le noeud est nul, il ne contient rien
            return false;
        } else if (key < r->key) { // Si la clé est plus petit que la clé du
            // noeud, l'élement recherché se trouve dans le sous-arbre gauche
            return contains(r->left, key);
        } else if (key > r->key) { // Si la clé est plus grand que la clé du
            // noeud, l'élement recherché se trouve dans le sous-arbre droit
            return contains(r->right, key);
        } else { // R.key = key
            return true;
        }
    }

public:
    //
    // @brief Recherche de la cle minimale.
    //
    // @return une const reference a la cle minimale
    //
    // @exception std::logic_error si necessaire
    //
    // vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
    //
    // @remark O(log(n))
    const_reference min() const { // l'élement min se trouve tout à gauche de l'arbre
        Node* temp = _root;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp->key;
    }

    //
    // @brief Supprime le plus petit element de l'arbre.
    //
    // @exception std::logic_error si necessaire
    //
    // vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
    //
    // @remark O(log(n))
    void deleteMin() {
        const value_type minKey = min();
        deleteElement(minKey);
    }


    //
    // @brief Supprime l'element de cle key de l'arbre.
    //
    // @param key l'element a supprimer
    //
    // si l'element n'est pas present, la fonction ne modifie pas
    // l'arbre mais retourne false. Si l'element est present, elle
    // retourne vrai
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée deleteElement(Node*&,const_reference)
    //
    // @remark O(log(n))
    bool deleteElement(const_reference key) noexcept {
        return deleteElement(_root, key);
    }

private:
    //
    // @brief Supprime l'element de cle key du sous arbre.
    //
    // @param r la racine du sous arbre
    // @param key l'element a supprimer
    //
    // si l'element n'est pas present, la fonction ne modifie pas
    // l'arbre mais retourne false. Si l'element est present, elle
    // retourne vrai
    //
    // @remark O(log(n))
    static bool deleteElement(Node*& r, const_reference key) noexcept {
        if (r == nullptr) { // Si r est nul, rien a supprimmer
            return false;
        }
        bool deleted;
        if (key < r->key) { // Si la clé à supprimer est plus petite que la clé du
            // neoeud, l'émeent se trouve dans le sous-arbre gauche
            deleted = deleteElement(r->left, key);
            if (deleted) r->nbElements--;
            return deleted;
        } else if (key > r->key) { // Si la clé à supprimer est plus petite que la
            // clé du neoeud, l'émeent se trouve dans le sous-arbre gauche
            deleted = deleteElement(r->right, key);
            if (deleted) r->nbElements--;
            return deleted;
        } else { //found
            if (r->right == nullptr) { // Si le fils droit n'existe pas, on
                // supprime simplement la feuille
                Node* temp = r;
                r = r->left;
                delete (temp);
                return true;
            } else if (r->left == nullptr) { // Si le fils gauche n'existe pas, on
                // supprime simplement la feuille
                Node* temp = r;
                r = r->right;
                delete (temp);
                return true;
            } else { // Possède deux fils
                Node* subTreeMin = r->right;
                Node* subTreeMinParent = nullptr;
                while (subTreeMin->left != nullptr) { // chercher le min dans le
                    // sous arrbre droit
                    subTreeMinParent = subTreeMin;
                    subTreeMin = subTreeMin->left;
                }

                subTreeMinParent->left = r; // on indque que le nouveau fils est
                // l'élement à supprimer
                std::swap(r, subTreeMin);
                // On swap les fils
                std::swap(r->left, subTreeMin->left);
                std::swap(r->right, subTreeMin->right);
                std::swap(r->nbElements, --subTreeMin->nbElements);
                deleteElement(r->right, subTreeMin->key);

                return true;
            }
        }
    }

public:
    //
    // @brief taille de l'arbre
    //
    // @return le nombre d'elements de l'arbre
    //
    // @remark O(1)
    size_t size() const noexcept {
        return _root->nbElements;
    }

    //
    // @brief cle en position n
    //
    // @return une reference a la cle en position n par ordre croissant des
    // elements
    //
    // @exception std::logic_error si nécessaire
    //
    // ajoutez le code de gestion des exceptions, puis mettez en oeuvre
    // la fonction recursive nth_element(Node*, n)
    //
    // @remark O(log(n))
    const_reference nth_element(size_t n) const {
        if (n > _root->nbElements)
            throw std::logic_error("La position est plus "
                                   "grand que le nombre "
                                   "d'éléments");
        return nth_element(_root, n);
    }

private:
    //
    // @brief cle en position n dans un sous arbre
    //
    // @param r la racine du sous arbre. ne peut pas etre nullptr
    // @param n la position n
    //
    // @return une reference a la cle en position n par ordre croissant des
    // elements
    //
    // @remark O(log(n))
    static const_reference nth_element(Node* r, size_t n) noexcept {
        assert(r != nullptr);
        size_t s = r->left == nullptr ? 0 : r->left->nbElements;
        if (n < s) {
            return nth_element(r->left, n);
        } else if (n > s) {
            return nth_element(r->right, n - s - 1);
        } else { //Found
            return r->key;
        }
    }

public:
    //
    // @brief position d'une cle dans l'ordre croissant des elements de l'arbre
    //
    // @param key la cle dont on cherche le rang
    //
    // @return la position entre 0 et size()-1, size_t(-1) si la cle est absente
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée rank(Node*,const_reference)
    //
    // @remark O(log(n))
    size_t rank(const_reference key) const noexcept {
        return rank(_root, key);
    }

private:
    //
    // @brief position d'une cle dans l'ordre croissant des elements du sous-arbre
    //
    // @param key la cle dont on cherche le rang
    // @param r la racine du sous arbre
    //
    // @return la position entre 0 et size()-1, size_t(-1) si la cle est absente
    //
    // @remark O(log(n))
    static size_t rank(Node* r, const_reference key) noexcept {
        if (r == nullptr || !contains(r, key)) { // Key not found
            return size_t(-1);
        } else if (key < r->key) {
            rank(r->left, key);
        } else if (key > r->key) {
            return rank(r->right, key) +
                   (r->left == nullptr ? 0 : r->left->nbElements) + 1;
        } else { // Key found
            return (r->left == nullptr ? 0 : r->left->nbElements);
        }
    }

public:
    //
    // @brief linearise l'arbre
    //
    // transforme l'arbre en une liste simplement chainee composee des memes
    // noeuds que precedemment, mais dont les pointeurs left sont tous egaux
    // a nullptr. Cette liste doit toujours respecter les conditions d'un
    // arbre binaire de recherche
    //
    // Ne pas modifier cette fonction qui sert essentiellement a tester la
    // fonction recursive linearize(Node*, Node*&, size_t&) utilisée par
    // la methode publique arborize
    //
    // @remark O(n)
    void linearize() noexcept {
        size_t cnt = 0;
        Node* list = nullptr;
        linearize(_root, list, cnt);
        _root = list;
    }

private:
    //
    // @brief linearise une sous arbre tree en une liste
    //
    // @param tree pointe vers la racine de l'arbre a lineariser
    // @param list reference a la tete de la liste a creer. sera modifiee
    //             par la fonction pour que list pointe vers le plus petit
    //             element de tree
    // @param cnt  calcule au fure et a mesure le nombre d'elements de la liste
    //             cree. l'effet de la fonction doit etre d'ajouter le nombre
    //             d'elements du sous-arbre de racine tree. Cependant, vous
    //             avez uniquement le droit d'utiliser l'opérateur ++.
    //
    // @remark O(n)
    static void linearize(Node* tree, Node*& list, size_t& cnt) noexcept {

        if (tree == nullptr) return;

        if (tree->right != nullptr) { // lineralise le coté droite
            linearize(tree->right, list, cnt);
        }

        tree->right = list;
        list = tree; //Ajoute la racine de l'arbre dans la liste
        cnt++;
        list->nbElements = cnt; // MAJ du nbre d'element

        if (tree->left != nullptr) { // lineralise le coté gauche
            linearize(tree->left, list, cnt);
        }

        tree->left = nullptr; // indique que le fils gauche n'existe pas (nullptr)
    }


public:
    //
    // @brief equilibre l'arbre
    //
    // applique l'algorithme d'equilibrage de l'arbre par linearisation et
    // arborisation
    //
    // Ne pas modifier cette fonction.
    //
    // @remark O(n)
    void balance() noexcept {
        size_t cnt = 0;
        Node* list = nullptr;
        linearize(_root, list, cnt);
        arborize(_root, list, cnt);
    }

private:
    //
    // @brief arborise les cnt premiers elements d'une liste en un arbre
    //
    // @param tree reference dans laquelle il faut ecrire la racine de l'arbre
    //             arborise par la fonction
    // @param list IN - reference a la tete de la liste a parcourir. La liste
    //                  est composee de Node dont le pointer left est nullptr
    //             OUT - debut de la suite de la liste dont on a utilise cnt
    //                   elements
    // @param cnt  nombre d'elements de la liste que l'on doit utiliser pour
    //             arboriser le sous arbre
    //
    // @remark O(n)
    static void arborize(Node*& tree, Node*& list, size_t cnt) noexcept {
        if (cnt == 0) {
            tree = nullptr;// Le le counter est à zero donc l'arbre est vide
            return;
        }

        Node* RG = list->right;
        arborize(RG, list, (cnt - 1) / 2); //arborise le noeud suivant dans la
        // liste, on remonte d'un hauteur dont le cnt est div par 2 et moins 1
        // pour le côté gauche de l'arbre

        tree = list; // on indique que la racine est le 1er elem de la list (pop())

        list->nbElements = cnt; // Maj du nbre d'élément

        tree->left = RG; // L'elem a droit est le suivant que la liste
        list = list->right; // Maj de la list, la tête de la liste est le noeud
        // suivant

        arborize(tree->right, list, cnt / 2); // on arborise le côté droit de
        // l'arbre, on remonte d'un hauteur dont le cnt est div par 2
    }

public:
    //
    // @brief Parcours pre-ordonne de l'arbre
    //
    // @param f une fonction capable d'être appelée en recevant une cle
    //          en parametre. Pour le noeud n courrant, l'appel sera
    //          f(n->key);
    //
    // @remark O(n)
    template<typename Fn>
    void visitPre(Fn f) {
        //Appele de la fonction récursive
        visitPre(f, _root);
    }

private :
    //
    // @brief Parcours pre-ordonne de l'arbre
    //
    // @param f une fonction capable d'être appelée en recevant une cle
    //          en parametre. Pour le noeud n courrant, l'appel sera
    //          f(n->key);
    // @param root  La racine de sous arbre actuelle
    //
    // @remark O(n)
    template<typename Fn>
    void visitPre(Fn f, Node* root) {
        if (root != nullptr) {
            f(root->key);
            visitPre(f, root->left);
            visitPre(f, root->right);
        }
    }

public:

    //
    // @brief Parcours symétrique de l'arbre
    //
    // @param f une fonction capable d'être appelée en recevant une cle
    //          en parametre. Pour le noeud n courrant, l'appel sera
    //          f(n->key);
    //
    // @remark O(n)
    template<typename Fn>
    void visitSym(Fn f) {
        //Appele de la fonction récursive
        visitSym(f, _root);
    }

private :


    //
    // @brief onction résusive privé pour le parcours symetrique de l'arbre
    //
    // @param f     une fonction capable d'être appelée en recevant une cle
    //              en parametre. Pour le noeud n courrant, l'appel sera
    //              f(n->key);
    // @param root  La racine de sous arbre actuelle
    //
    // @remark O(n)
    template<typename Fn>
    void visitSym(Fn f, Node* root) {
        if (root != nullptr) {
            visitSym(f, root->left);
            f(root->key);
            visitSym(f, root->right);
        }
    }

public:

    //
    // @brief Parcours post-ordonne de l'arbre
    //
    // @param f une fonction capable d'être appelée en recevant une cle
    //          en parametre. Pour le noeud n courrant, l'appel sera
    //          f(n->key);
    //
    // @remark O(n)
    template<typename Fn>
    void visitPost(Fn f) {
        //Appele de la fonction récursive
        visitPost(f, _root);
    }

private :

    //
    // @brief Parcours post-ordonne de l'arbre
    //
    // @param f une fonction capable d'être appelée en recevant une cle
    //          en parametre. Pour le noeud n courrant, l'appel sera
    //          f(n->key);
    // @param root  La racine de sous arbre actuelle
    //
    // @remark O(n)
    template<typename Fn>
    void visitPost(Fn f, Node* root) {
        if (root != nullptr) {
            visitPost(f, root->left);
            visitPost(f, root->right);
            f(root->key);
        }
    }

public:


    //
    // Les fonctions suivantes sont fournies pour permettre de tester votre classe
    // Merci de ne rien modifier au dela de cette ligne
    //
    void display() const {
        stringstream ss1, ss2, ss3;
        displayKeys(ss1);
        displayKeys(ss3);
        displayCounts(ss2);
        string l1, l2;

        size_t W = 11;
        while (getline(ss3, l1))
            if (l1.length() > W) W = l1.length();

        displayKeys(ss1);

        cout << "\n";
        cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W)
             << "-" << setfill(' ') << "+" << endl;
        cout << "| " << left << setw(W) << "key" << "| " << setw(W)
             << "nbElements"
             << "|" << endl;
        cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W)
             << "-" << setfill(' ') << "+" << endl;
        while (getline(ss1, l1) and getline(ss2, l2)) {
            cout << "| " << left << setw(W) << l1 << "| " << setw(W) << l2 << "|"
                 << endl;
        }
        cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W)
             << "-" << setfill(' ') << "+" << endl;

    }

    void displayKeys(ostream& os = cout) const {
        display([](Node* n) -> const_reference { return n->key; }, os);
    }

    void displayCounts(ostream& os = cout) const {
        display([](Node* n) -> size_t { return n->nbElements; }, os);
    }

    //
    // utilise un parcours de l'arbre en largeur avec
    // un noeud sentinelle newLevel qui traque les
    // changements de niveaux
    //
    template<typename Fn>
    void display(Fn func, ostream& os = cout) const {
        Node* newLevel = (Node*) -1;
        // addresse non nulle dont on est sur qu'elle ne contient pas
        // vraiment un Node. Utilisée comme sentinelle.

        queue<Node*> Q;
        Q.push(_root);
        Q.push(newLevel);

        while (!Q.empty()) {
            Node* cur = Q.front();
            Q.pop();

            if (cur == newLevel) {
                os << endl;
                if (!Q.empty())
                    Q.push(newLevel);
            } else if (cur == nullptr) {
                os << "- ";
            } else {
                os << func(cur) << " ";
                Q.push(cur->left);
                Q.push(cur->right);
            }
        }
    }
};