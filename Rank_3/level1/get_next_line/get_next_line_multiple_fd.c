#include <unistd.h>
#include <stdlib.h>

// Structure to hold state for each file descriptor
typedef struct s_fd_state
{
    int fd;
    char buffer[BUFFER_SIZE + 1];
    int buffer_pos;
    int buffer_size;
    char temp_line[100000];
    int line_len;
    struct s_fd_state *next;
} t_fd_state;

// Find or create state for given fd
t_fd_state *get_fd_state(int fd, t_fd_state **head)
{
    t_fd_state *current = *head;
    t_fd_state *new_state;
    
    // Search for existing state
    while (current)
    {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    
    // Create new state
    new_state = malloc(sizeof(t_fd_state));
    if (!new_state)
        return NULL;
    
    new_state->fd = fd;
    new_state->buffer_pos = 0;
    new_state->buffer_size = 0;
    new_state->line_len = 0;
    new_state->next = *head;
    *head = new_state;
    
    return new_state;
}

// Remove state for given fd (cleanup)
void remove_fd_state(int fd, t_fd_state **head)
{
    t_fd_state *current = *head;
    t_fd_state *prev = NULL;
    
    while (current)
    {
        if (current->fd == fd)
        {
            if (prev)
                prev->next = current->next;
            else
                *head = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

char *get_next_line(int fd)
{
    static t_fd_state *fd_states = NULL;
    t_fd_state *state;
    char *line;
    int i;
    
    // Check for invalid fd
    if (fd < 0)
        return NULL;
    
    // Get state for this fd
    state = get_fd_state(fd, &fd_states);
    if (!state)
        return NULL;
    
    while (1)
    {
        // If buffer is empty, read new data
        if (state->buffer_pos >= state->buffer_size)
        {
            state->buffer_size = read(fd, state->buffer, BUFFER_SIZE);
            state->buffer_pos = 0;
            
            // If read error or EOF
            if (state->buffer_size <= 0)
            {
                if (state->line_len == 0)
                {
                    // No data to return, cleanup this fd
                    remove_fd_state(fd, &fd_states);
                    return NULL;
                }
                break; // EOF but we have data to return
            }
        }
        
        // Process current buffer
        while (state->buffer_pos < state->buffer_size)
        {
            state->temp_line[state->line_len] = state->buffer[state->buffer_pos];
            state->buffer_pos++;
            state->line_len++;
            
            // Found newline - finish the line
            if (state->temp_line[state->line_len - 1] == '\n')
            {
                state->temp_line[state->line_len] = '\0';
                
                // Allocate final line
                line = malloc(state->line_len + 1);
                if (!line)
                    return NULL;
                
                // Copy line
                i = 0;
                while (i < state->line_len)
                {
                    line[i] = state->temp_line[i];
                    i++;
                }
                line[i] = '\0';
                
                // Reset line length for next call
                state->line_len = 0;
                
                return line;
            }
        }
    }
    
    // EOF reached but we have data
    if (state->line_len > 0)
    {
        state->temp_line[state->line_len] = '\0';
        
        line = malloc(state->line_len + 1);
        if (!line)
            return NULL;
        
        i = 0;
        while (i < state->line_len)
        {
            line[i] = state->temp_line[i];
            i++;
        }
        line[i] = '\0';
        
        // Cleanup this fd since we're done
        remove_fd_state(fd, &fd_states);
        
        return line;
    }
    
    return NULL;
}
