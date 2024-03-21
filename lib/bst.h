#include <iostream>
#include <utility>

template<typename T>
struct _Node {
    _Node<T>* left_child;
    _Node<T>* right_child;
    _Node<T>* parent;
    T key;
    _Node(T val, _Node<T>* p) : parent(p), key(val), left_child(nullptr), right_child(nullptr) {}
    _Node() : key(0), left_child(nullptr), right_child(nullptr) {}
    ~_Node() = default;
};

class inorder {
    //this is a tag
};

class postorder {
    // this is also a tag
};

class preorder {
    // and this is a tag too
};

enum class Direction {
    forward,
    reverse
};

template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<_Node<T>>>
class bst {
protected:
    _Node<T>* root;
    size_t _size;
    static _Node<T>* leftmost(_Node<T>* node) {
        if(node == nullptr) {
            return nullptr;
        }
        while(node->left_child != nullptr) {
            node = node->left_child;
        }
        return node;
    }
    static _Node<T>* rightmost(_Node<T>* node) {
        if(node == nullptr) {
            return nullptr;
        }
        while(node->right_child != nullptr) {
            node = node->right_child;
        }
        return node;
    }
    static _Node<T>* right_ancestor(_Node<T>* node) {
        Compare comp;
        _Node<T>* successor = nullptr;
        _Node<T>* cur = node; 
        while(cur->parent != nullptr) {
            cur = cur->parent;
        }
        while(cur != nullptr) {
            if (!comp(node->key, cur->key) && !comp(cur->key, node->key)) {
                break;
            }
            if (comp(node->key, cur->key)) {
                successor = cur;
                cur = cur->left_child;
            } else {
                cur = cur->right_child;
            }
        }
        return successor;
    }
    static _Node<T>* left_ancestor(_Node<T>* node) {
        Compare comp;
        _Node<T>* successor = nullptr;
        _Node<T>* cur = node;
        while(cur->parent != nullptr) {
            cur = cur->parent;
        }
        while(cur != nullptr) {
            if (!comp(node->key, cur->key) && !comp(cur->key, node->key)) {
                break;
            }
            if(comp(node->key, cur->key)) {
                cur = cur->left_child;
            } else {
                successor = cur;
                cur = cur->right_child;
            }
        }
        return successor;
    }
    _Node<T>* _Find(T val) {
        Compare comp;
        _Node<T>* cur = root;
        while(cur != nullptr) {
            if(!comp(cur->key, val) && !comp(val, cur->key)) {
                return cur;
            }
            else if(comp(cur->key, val)) {
                cur = cur->right_child;
            } else {
                cur = cur->left_child;
            }
        }
        return nullptr;
    }
    _Node<T>* _Insert(_Node<T>* tree_root, T to_insert) {
        Compare comp;
        Allocator custom_allocator;
        if(tree_root == nullptr) {
            ++_size;
            root = std::allocator_traits<Allocator>::allocate(custom_allocator, 1);
            std::allocator_traits<Allocator>::construct(custom_allocator, root, to_insert, nullptr);
            return root;
        }
        _Node<T>* current = tree_root;
        _Node<T>* parent = nullptr;
        while (current != nullptr) {
            if(!comp(current->key, to_insert) && !comp(to_insert, current->key)) {
                return nullptr;
            }
            parent = current;
            if (comp(to_insert,current->key)) {
                current = current->left_child;
            } else {
                current = current->right_child;
            }
        }
        if(comp(to_insert,parent->key)) {
            ++_size;
            parent->left_child = std::allocator_traits<Allocator>::allocate(custom_allocator, 1);
            std::allocator_traits<Allocator>::construct(custom_allocator, parent->left_child, to_insert, parent);
            return parent->left_child;
        } else {
            ++_size;
            parent->right_child = std::allocator_traits<Allocator>::allocate(custom_allocator, 1);
            std::allocator_traits<Allocator>::construct(custom_allocator, parent->right_child, to_insert, parent);
            return parent->right_child;
        }
    }
    _Node<T>* _Previous(T val, _Node<T>* curr) {
        Compare comp;
        _Node<T>* successor = nullptr;
        while(curr != nullptr) {
            if(comp(curr->key, val)) {
                successor = curr;
                curr = curr->right_child;
            }
            else {
                curr = curr->left_child;
            }
        }
        return successor;
    } 
    _Node<T>* _Next(T val, _Node<T>* curr) {
        _Node<T>* successor = nullptr;
        Compare comp;
        while(curr != nullptr) {
            if(comp(val, curr->key)) {
                successor = curr;
                curr = curr->left_child;
            }
            else {
                curr = curr->right_child;
            }
        }
        return successor;
    }
    _Node<T>* _Copy(_Node<T>* node, _Node<T>* parent) {
        if(node == nullptr) {
            return nullptr;
        }
        Allocator custom_allocator;
        _Node<T>* new_node = std::allocator_traits<Allocator>::allocate(custom_allocator, 1);
        std::allocator_traits<Allocator>::construct(custom_allocator, new_node, node->key, parent);
        new_node->left_child = _Copy(node->left_child, new_node);
        new_node->right_child = _Copy(node->right_child, new_node);
        return new_node;
    }       
    void _Delete(_Node<T>* current) {
        if(current) {
            _Delete(current->left_child);
            _Delete(current->right_child);
            delete current;
        }
    }
    bool _Equals(_Node<T>* left, _Node<T>* right) {
        if(!left && !right) {
            return true;
        }
        if(!left || !right) {
            return false;
        }
        if(left->key != right->key) {
            return false;
        }
    }

    _Node<T>* _Erase(_Node<T>* curr, T value)
    {
        Compare comp;
        if (curr == nullptr) {
            return curr;
        }
        if (comp(value, curr->key)) {
            curr->left_child = _Erase(curr->left_child, value);
            return curr;
        }
        else if (comp(curr->key, value)) {
            curr->right_child = _Erase(curr->right_child, value);
            return curr;
        }
        if (curr->left_child == nullptr) {
            _Node<T>* temp = curr->right_child;
            --_size;
            delete curr;
            return temp;
        }
        else if (curr->right_child == nullptr) {
            _Node<T>* temp = curr->left_child;
            --_size;
            delete curr;
            return temp;
        } else {
            _Node<T>* succ_parent = curr;
            _Node<T>* succ = curr->right_child;
            while (succ->left_child != nullptr) {
                succ_parent = succ;
                succ = succ->left_child;
            }
            if (succ_parent != curr) {
                succ_parent->left_child = succ->right_child; 
            } else {
                succ_parent->right_child = succ->right_child;
            }
            curr->key = succ->key;
            --_size;
            delete succ;
            return curr;
        }
    }
public:
    template<typename IteratorType, Direction dir = Direction::forward>
    class order {
    protected:
        _Node<T>* current;
        _Node<T>* _root;
        _Node<T>* _Last(preorder tag, _Node<T>* cur) {
            while(cur->parent != nullptr) {
                cur = cur->parent;
            }
            
            while(true) {
                if(cur->right_child) {
                    cur = cur->right_child;
                } else if(cur->left_child) {
                    cur = cur->left_child;
                } else {
                    break;
                }
            }
            return cur;
        }
        _Node<T>* _Last(inorder tag, _Node<T>* cur) {
            while(cur->parent != nullptr) {
                cur = cur->parent;
            }
            return bst::rightmost(cur); 
        }
        _Node<T>* _Last(postorder tag, _Node<T>* cur) {
            while(cur->parent != nullptr) {
                cur = cur->parent;
            }
            return cur;
        }
        order successor(preorder tag) {
            if(this->current->left_child != nullptr) {
                this->current = this->current->left_child;  
                return *this;
            }
            if(this->current->right_child != nullptr) {
                this->current = this->current->right_child;
                return *this;
            }
            if(this->current->parent != nullptr && 
            this->current->parent->left_child == this->current && 
            this->current->parent->right_child != nullptr) {
                this->current = this->current->parent->right_child;
                return *this;
            }
            while(this->current->parent != nullptr) {
                this->current = this->current->parent;
                if(this->current->parent != nullptr && 
                this->current->parent->left_child == this->current && 
                this->current->parent->right_child != nullptr) {
                    this->current = this->current->parent->right_child;
                    return *this;
                }
            }
            this->current = nullptr;
            return *this;
        }
        order successor(inorder tag) {
            if(this->current->right_child != nullptr) {
                this->current = bst::leftmost(this->current->right_child);
                return *this;
            }
            this->current = bst::right_ancestor(this->current);
            return *this;
        }
        order successor(postorder tag) {
            if(this->current->parent == nullptr) {
                this->current = nullptr;
                return *this;
            }
            if(this->current->parent->right_child == this->current) {
                this->current = this->current->parent;
                return *this;
            }
            if(this->current->parent->right_child != nullptr) {
                _Node<T>* leaf = this->current->parent->right_child;
                while(!(leaf->right_child == nullptr && leaf->left_child == nullptr)) {
                    if(leaf->left_child != nullptr) {
                        leaf = leaf->left_child;
                    } else {
                        leaf = leaf->right_child;
                    }   
                }
                this->current = leaf;
                return *this;
            }
            this->current = this->current->parent;
            return *this;
        }
        
        order predecessor(preorder tag) {
            if(this->current->parent == nullptr) {
                this->current = nullptr;
                return *this;
            }
            if(this->current->parent->right_child == this->current &&
            this->current->parent->left_child != nullptr) {
                this->current = this->current->parent->left_child;
                while(true) {
                    if(this->current->right_child) {
                        this->current = this->current->right_child;
                    } else if(this->current->left_child) {
                        this->current = this->current->left_child;
                    } else {
                        break;
                    }
                }
                return *this;
            }
            this->current = this->current->parent;
            return *this;
        }
        order predecessor(inorder tag) {
            if(this->current->left_child != nullptr) {
                this->current = bst::rightmost(this->current->left_child);
                return *this;
            }
            this->current = bst::left_ancestor(this->current);
            return *this;
        }
        order predecessor(postorder tag) {
            if(this->current->right_child != nullptr) {
                this->current = this->current->right_child;
                return *this;
            }
            if(this->current->left_child != nullptr) {
                this->current = this->current->left_child;
                return *this;
            }
            if(this->current->parent != nullptr &&  this->current->parent->right_child == this->current && 
            this->current->parent->left_child != nullptr) {
                this->current = this->current->parent->left_child;
                return *this;
            }
            while(this->current->parent != nullptr) {
                this->current = this->current->parent;
                if(this->current->parent != nullptr && 
                this->current->parent->right_child == this->current && 
                this->current->parent->left_child != nullptr) {
                    this->current = this->current->parent->left_child;
                    return *this;
                }
            }
            this->current = nullptr;
            return *this;
        }
    public:
        order() : current(nullptr) {};
        order(_Node<T>* ptr) : current(ptr) {};
        order(preorder tag, bool begin, _Node<T>* tree_root, Direction d) {
            this->_root = tree_root;
            if(d == Direction::reverse) {
                if(!begin) {
                    this->current = nullptr;
                    return;
                }
                this->current = bst::rightmost(tree_root);
                return;
            }
            if(!begin) {
                this->current = nullptr;
                return;
            }
            this->current = tree_root;
        }
        order(inorder tag, bool begin, _Node<T>* tree_root, Direction d) {
            this->_root = tree_root;
            if(d == Direction::reverse) {
                if(!begin) {
                    this->current = nullptr;
                    return;
                }
                this->current = bst::rightmost(tree_root);
                return;
            }
            if(!begin) {
                this->current = nullptr;
                return;
            }
            this->current = bst::leftmost(tree_root);
        }
        order(postorder tag, bool begin, _Node<T>* tree_root, Direction d) {
            this->_root = tree_root;
            if(d == Direction::reverse) {
                if(!begin) {
                    this->current = nullptr;
                    return;
                }
                this->current = tree_root;
                return;
            }
            if(!begin) {
                this->current = nullptr;
                return;
            }
            this->current = tree_root;
            while(!(this->current->right_child == nullptr && this->current->left_child == nullptr)) {
                if(this->current->left_child != nullptr) {
                    this->current = this->current->left_child;
                } else {
                    this->current = this->current->right_child;
                }   
            }
        }
        order& operator=(const order& other) { 
            this->current = other.current;
            return *this;
        }
        order(const order& other) : current(other.current) {}
        order operator++(){ 
            IteratorType tag;
            if constexpr(dir == Direction::forward) {
                if(this->current == nullptr) {
                    return *this;
                }
                successor(tag);
                return *this;
            } else if constexpr(dir == Direction::reverse) {
                if(this->current == nullptr) {
                    return *this;
                }
                predecessor(tag);
                return *this;
            }
        }
        order operator--(){
            IteratorType tag;
            if constexpr(dir == Direction::forward) {
                if(this->current == nullptr) {
                    this->current = _Last(tag, _root);
                    return *this;
                }
                predecessor(tag);
                return *this;
            } else if constexpr(dir == Direction::reverse) {
                if(this->current == nullptr) {
                    order temp(tag, true, _root, Direction::forward);
                    this->current = temp.current;
                    return *this;
                }
                successor(tag);
                return *this;
            }
        }
        order operator++(int) {
            order tmp = *this;
            ++(*this);
            return tmp;
        }
        order operator--(int) {
            order tmp = *this;
            --(*this);
            return tmp;
        }
        const T& operator*() const {
            if(this->current == nullptr) {
                throw std::out_of_range("iterator out of range");
            }
            return current->key;
        }
        bool operator==(const order& other) const {
            return this->current == other.current;
        }
        bool operator!=(const order& other) const {
            return this->current != other.current;
        }
    };

    bst() : root(nullptr), _size(0) {}
    template<class Tag = inorder,class Constructor_compare>
    bst(order<Tag> i, order<Tag> j, Constructor_compare comp) {
        _size = 0;
        for(; i != j; ++i) {
            insert(*i);
        }
    }
    template<class Tag = inorder>
    bst(order<Tag> i, order<Tag> j) {
        _size = 0;
        Compare comp;
        for(; i != j; ++i) {
            insert(*i);
        }
    }
    bst(std::initializer_list<T> list) {
        _size = 0;
        root = nullptr;
        for (const T& element : list) {
            insert(element);
        }
    }

    bst(const bst<T>& other) {
        this->root = _Copy(other.root, nullptr);
        this->_size = other._size;
    }
    ~bst() {
        _Delete(root);
    }
    bst& operator=(const bst& other) {
        if(this == &other) {
            return *this;
        }
        _Delete(this->root);
        this->root = _Copy(other.root, nullptr);
        this->_size = other._size;
        return *this;
    }
    bool operator==(const bst& other) const {
        if(this->size() != other.size()) {
            return false;
        }
        return _Equals(this->root, other.root);
    }
    bool operator!=(const bst& other) const {
        return !(*this==other);
    }
    void swap(bst<T>& other) {
        _Node<T>* temp = this->root;
        this->root = other->root;
        other->root = temp;
    }
    template<typename Tag = inorder>
    order<Tag> begin() {
        Tag tag;
        return order<Tag>(tag, 1, root, Direction::forward);
    }
    template<typename Tag = inorder>
    order<Tag> end() {
        Tag tag;
        return order<Tag>(tag, 0, root, Direction::forward);
    }   
    template<typename Tag = inorder>
    order<Tag> cbegin() {
        Tag tag;
        return order<Tag>(tag, 1, root, Direction::forward);
    }
    template<typename Tag = inorder>
    order<Tag> cend() {
        Tag tag;
        return order<Tag>(tag, 0, root, Direction::forward);
    }   
    
    template<typename Tag = inorder>
    order<Tag, Direction::reverse> rbegin() {
        Tag tag;
        return order<Tag, Direction::reverse>(tag, 1, root, Direction::reverse);
    }
    template<typename Tag = inorder>
    order<Tag, Direction::reverse> rend() {
        Tag tag;
        return order<Tag, Direction::reverse>(tag, 0, root, Direction::reverse);
    }   
    
    template<typename Tag = inorder>
    order<Tag, Direction::reverse> crbegin() {
        Tag tag;
        return order<Tag, Direction::reverse>(tag, 1, root, Direction::reverse);
    }
    template<typename Tag = inorder>
    order<Tag, Direction::reverse> crend() {
        Tag tag;
        return order<Tag, Direction::reverse>(tag, 0, root, Direction::reverse);
    }   
    
    bool empty() {
        return (this->begin() == this->end());
    }
    size_t size() {
        return _size;
    }
    size_t max_size() {
        return SIZE_MAX;
    }
    template<typename Tag = inorder>
    std::pair<order<Tag>, bool> insert(T value) {
        _Node<T>* inserted = _Insert(root, value);
        order<Tag> iter(inserted);
        return std::pair<order<Tag>, bool>(iter, (inserted != nullptr));
    }
    template<typename Tag = inorder>
    std::pair<order<Tag>, bool> insert(order<Tag> p, T value) {
        _Node<T>* inserted = _Insert(root, value);
        order<Tag> iter(inserted);
        return std::pair<order<Tag>, bool>(iter, (inserted != nullptr));
    }
    template<typename Tag = inorder>
    void insert(order<Tag> i, order<Tag> j) {
        for(; i != j; ++i) {
            insert(*i);
        }
    }
    _Node<T> extract(T k) {
        _Node<T> extracted = *(_Find(k));
        erase(k);
        return extracted;
    }
    void merge(const bst<T>& other) { 
        for(auto it = other.begin(); it != other.end(); ++it) {
            insert(*it);
        }
    }
    template<typename Tag = inorder>
    order<Tag> erase(order<Tag> q1, order<Tag> q2) {
        for(; q1 != q2; ++q1) {
            erase(*q1);
        }
        return q2;
    }
    void clear() {
        for(auto it = begin<inorder>(); it != end<inorder>(); ++it) {
            erase(*it);
        }
    }
    template<typename Tag = inorder>
    order<Tag> erase(T val) {
        _Node<T>* curr = _Find(val);
        order<Tag> it(curr);
        ++it;
        root = _Erase(root, val);
        return it;
    }
    template<typename Tag = inorder>
    order<Tag> erase(order<Tag> iterator) { 
        order<Tag> it = iterator;
        _Node<T>* temp = iterator.current;
        ++it;
        root = _Erase(root, temp->key);
        return it;
    }
    template<typename Tag = inorder>
    order<Tag> find(T val) {
        _Node<T>* curr = _Find(val);
        order<Tag> it(curr);
        return it;
    }
    bool contains(T val) {
        _Node<T>* curr = _Find(val);
        return (curr != nullptr);
    }
    template<typename Tag = inorder>
    order<Tag> lower_bound(T val) {
        _Node<T>* curr = _Previous(val, root);
        order<Tag> it(curr);
        return it;
    }
    template<typename Tag = inorder>
    order<Tag> upper_bound(T val) {
        _Node<T>* curr = _Next(val, root);
        order<Tag> it(curr);
        return it;
    }
    template<typename Tag = inorder>
    std::pair<order<Tag>, order<Tag>> equal_range(T val) {
        return std::make_pair(lower_bound(val), upper_bound(val));
    }
    template<typename Tag>
    Compare key_comp() {
        Compare comp;
        return comp;
    }
    Compare value_comp() {
        Compare comp;
        return comp;
    }
};
