/*---------------------------------------------------------------------------*/
static void
recv_mesh(struct mesh_conn *mesh, const rimeaddr_t *from, uint8_t hops)
{
  struct rudolph1mh_conn *c = (struct rudolph1mh_conn *) ((char *) mesh
      - offsetof(struct rudolph1mh_conn, mesh));
  struct rudolph1mh_datapacket *p = packetbuf_dataptr();

  PRINTF("%d.%d: Got mesh type %d from %d.%d\n",
      rimeaddr_node_addr.u8[0], rimeaddr_node_addr.u8[1],
      p->h.type, from->u8[0], from->u8[1]);

  if(!rimeaddr_cmp(&c->partner, from)){
    if(!rimeaddr_cmp(&c->partner, &rimeaddr_null)){
      rimeaddr_t lfrom;
      PRINTF("%d.%d: Unexpected packet from %d.%d\n",
            rimeaddr_node_addr.u8[0], rimeaddr_node_addr.u8[1],
            from->u8[0], from->u8[1]);
      rimeaddr_copy(&lfrom, from);
      send_busy(c, &lfrom);
      return;
    } else {
      rimeaddr_copy(&c->partner, from);
    }
  }


  if(p->h.type == TYPE_ACK){
    if(p->h.s_id == c->s_id && p->h.chunk == c->highest_chunk){
      ctimer_stop(&c->t);
      rimeaddr_copy(&c->partner, &rimeaddr_null);
      if(c->cb->read_done){
        c->cb->read_done(c);
      }
      PRINTF("GOT ACK\n");
    } else {
      PRINTF("Unexpected ACK sid %i,%i C %i,%i\n", p->h.s_id, c->s_id, p->h.chunk, c->highest_chunk);
    }



  } else if(p->h.type == TYPE_NACK) {
    c->nacks++;
    PRINTF("%d.%d: Got NACK for %d:%d (%d:%d)\n",
        rimeaddr_node_addr.u8[0], rimeaddr_node_addr.u8[1],
        p->h.s_id, p->h.chunk,
        c->s_id, c->chunk);
    if(p->h.s_id == c->s_id) {
      if(p->h.chunk < c->chunk) {
        /* Format and send a repair packet */
        PRINTF("%d.%d: sending repair for chunk %d\n",
            rimeaddr_node_addr.u8[0], rimeaddr_node_addr.u8[1],
            p->h.chunk);
        format_data(c, p->h.chunk);
        mesh_send(&c->mesh, &c->partner);
      }
    }
    else if(LT(p->h.s_id, c->s_id)) {
      format_data(c, 0);
      mesh_send(&c->mesh, &c->partner);
    }
  }
  else if(p->h.type == TYPE_DATA ) {
    /* This is a repair packet from someone else. */
    PRINTF("%d.%d: got chunk %d\n",
        rimeaddr_node_addr.u8[0], rimeaddr_node_addr.u8[1],
        p->h.chunk);
    handle_data(c, p);
  } else if(p->h.type == TYPE_FIN ) {
    /* This is a repair packet from someone else. */
    PRINTF("%d.%d: got last chunk %d\n",
        rimeaddr_node_addr.u8[0], rimeaddr_node_addr.u8[1],
        p->h.chunk);
    if(!rimeaddr_cmp(&c->partner, &rimeaddr_null)){
      handle_data(c, p);
    }{
      rimeaddr_copy(&c->partner, from);
    }
    send_ack(c);
    rimeaddr_copy(&c->partner, &rimeaddr_null);

  } else if(p->h.type == TYPE_BUSY){
    PRINTF("%d.%d: %d.%d is busy\n",
        rimeaddr_node_addr.u8[0], rimeaddr_node_addr.u8[1],
        from->u8[0], from->u8[1]);
    //Wait
  }
}