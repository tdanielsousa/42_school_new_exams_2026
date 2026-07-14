#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static int buffer_pos = 0;
    static int buffer_size = 0;
    char *line;
    int line_len = 0;
    int i;
    
    // Simple large buffer approach - no dynamic allocation during building
    static char temp_line[100000]; // Large buffer to avoid malloc during line building
    
    // Check for invalid fd
    if (fd < 0)
        return NULL;
    
    while (1)
    {
        // If buffer is empty, read new data
        if (buffer_pos >= buffer_size)
        {
            buffer_size = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            
            // If read error or EOF with no data collected
            if (buffer_size <= 0)
            {
                if (line_len == 0)
                    return NULL;
                break; // EOF but we have data to return
            }
        }
        
        // Process current buffer
        while (buffer_pos < buffer_size)
        {
            temp_line[line_len] = buffer[buffer_pos];
            buffer_pos++;
            line_len++;
            
            // Found newline - finish the line
            if (temp_line[line_len - 1] == '\n')
            {
                temp_line[line_len] = '\0';
                
                // Allocate final line
                line = malloc(line_len + 1);
                if (!line)
                    return NULL;
                
                // Copy line
                i = 0;
                while (i < line_len)
                {
                    line[i] = temp_line[i];
                    i++;
                }
                line[i] = '\0';
                
                return line;
            }
        }
    }
    
    // EOF reached but we have data
    if (line_len > 0)
    {
        temp_line[line_len] = '\0';
        
        line = malloc(line_len + 1);
        if (!line)
            return NULL;
        
        i = 0;
        while (i < line_len)
        {
            line[i] = temp_line[i];
            i++;
        }
        line[i] = '\0';
        
        return line;
    }
    
    return NULL;
}
