    public void connect(TreeLinkNode root) {
        if (root == null)
            return;
        Queue<TreeLinkNode> queue = new LinkedList<TreeLinkNode>();
        queue.add(root);
        queue.add(null);

        while (!queue.isEmpty()) {
            TreeLinkNode out = queue.remove();
            if (out != null) {
                out.next = queue.peek();
                if (out.left != null)
                    queue.add(out.left);
                if (out.right != null)
                    queue.add(out.right);
            } else {
                if (!queue.isEmpty()) {
                    queue.add(null);
                }

            }

        }

    }