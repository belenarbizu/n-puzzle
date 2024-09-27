class Heap
{

    constructor(key)
    {
        this.key = key;
        this.heap = [];
        this.max_elements_allocated = 0;
    }

    _update_max_elements_allocated()
    {
        if (this.length() > this.max_elements_allocated)
            this.max_elements_allocated = this.length();
    }

    _swap(a, b)
    {
        let tmp = this.heap[a];
        this.heap[a] = this.heap[b];
        this.heap[b] = tmp;
    }

    _get_key(node)
    {
        if (node["key"])
        {
            return node["key"];
        }
        else
        {
            node["key"] = this.key(node["node"]);
            return node["key"];
        }
    }

    _parent_of(i)
    {
        return Math.floor(i - 1 / 2);
    }

    _child_of(i, child_n)
    {
        return 2 * i + child_n;
    }

    push(element)
    {
        element = {"node":element, "key":null};

        let node_key = this._get_key(element);

        // Add the new node at the end of the heap
        let i = this.heap.length;
        this.heap.push(element);
    
        let need_swap = true;
        while (i > 0 && need_swap)
        {
            let parent_i = this._parent_of(i);
            let parent_key = this._get_key(this.heap[parent_i]);

            // Swap the parent and the node if needed
            if (parent_key > node_key)
            {
                this._swap(parent_i, i);
                i = parent_i;
            }
            else
                need_swap = false;
        }

        this._update_max_elements_allocated();
    }

    pop()
    {
        // Swap the root node with last node
        this._swap(0, this.length() - 1);

        // Remove the root node by popping the last item out of the array
        let element = this.heap.pop();

        let i = 0;
        let need_swap = true;

        while (this._child_of(i, 1) < this.length() && need_swap)
        {
            let key = this._get_key(this.heap[i]);

            let left_child_i = this._child_of(i, 1);
            let left_child_key = this._get_key(this.heap[left_child_i]);
            let min_child_i = left_child_i;

            let right_child_i = this._child_of(i, 2);
            if (right_child_i < this.length())
            {
                let right_child_key = this._get_key(this.heap[right_child_i]);

                if (right_child_key < left_child_key)
                {
                    min_child_i = right_child_i;
                }
            }

            if (this._get_key(this.heap[min_child_i])
                < this._get_key(this.heap[i]))
            {
                this._swap(i, min_child_i);
            }
            else
                // If key is less than both of it's children keys then heap 
                // is stable
                need_swap = false;

            i = min_child_i;
        }

        return element["node"];
    }

    length()
    {
        return this.heap.length;
    }

    get_max_elements_allocated()
    {
        return this.max_elements_allocated;
    }

}


function sort_test()
{
    let n = 5000;
    let my_heap = new Heap((o)=>{return o;})

    for (let i = 0; i < n; i++)
    {
        my_heap.push(Math.floor(Math.random() * 1000));
    }

    let last = -1;
    let failed = false;
    while(my_heap.length() > 0)
    {
        let next = my_heap.pop();
        if (next < last)
            failed = true;
        last = next;
    }

    if (failed)
        console.log("Test failed");
    else
        console.log("Test passed");
}

sort_test();
