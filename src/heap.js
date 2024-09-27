class Heap
{

    constructor(key)
    {
        this.key = key;
        this.heap = [];
    }

    _swap(a, b)
    {
        let tmp = this.heap[a];
        this.heap[a] = this.heap[b];
        this.heap[b] = tmp;
    }

    _get_key(node)
    {
        if (node._heap_key)
        {
            return node._heap_key;
        }
        else
        {
            node._heap_key = this.key(node);
            return node._heap_key;
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

    push(node)
    {
        node = [node];

        const node_key = this._get_key(node);

        // Add the new node at the end of the heap
        let i = this.heap.length;
        this.heap.push(node);
    
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
    }

    pop()
    {
        // Swap the root node with last node
        this._swap(0, this.heap.length - 1);

        // Remove the root node by popping the last item out of the array
        let node = heap.pop();

        let i = 0;
        let need_swap = true;

        while (this._child_of(i, 1) < this.heap.length && need_swap)
        {
            let left_child_i = this._child_of(i, 1);
            let right_child_i = this._child_of(i, 2);
            let left_child_key = this._get_key(this.heap[left_child_i]);
            let right_child_key = this._get_key(this.heap[right_child_i]);
            let key = this._get_key(this.heap[i]);

            let min_child_i = right_child_i;
            if (left_child_key < right_child_key)
            {
                min_child_i = left_child_i;
            }

            if (this._get_key(this.heap[min_child_i])
                < this._get_key(this.heap[i]))
            {
                this._swap(i, min_child_i);
                i = min_child_i;
            }
            else
                // If key is less than both of it's children keys then heap 
                // is stable
                need_swap = false;
        }

        return node[0];
    }

}

