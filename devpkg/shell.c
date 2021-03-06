#include "shell.h"
#include "dbg.h"
#include <stdarg.h>

// Load up shell template with specified arguments, then use
// Shell_run to actually execute those commands in the shell
int Shell_exec(Shell template, ...)
{
  apr_pool_t *p = NULL;
  int rc = -1;
  apr_status_t rv = APR_SUCCESS;
  va_list argp;
  const char *key = NULL;
  const char *arg = NULL;
  int i = 0;
  int num_args = 0;

  rv = apr_pool_create(&p, NULL);
  check(rv == APR_SUCCESS, "Failed to create pool.");

  // Start to get all arguments after template in the arg list
  va_start(argp, template);

  for(key = va_arg(argp, const char *);
      key != NULL;
      key = va_arg(argp, const char *))
    {
      // Alternate arg list: key arg key arg key arg
      arg = va_arg(argp, const char *);
      // Go through the template's arg list and find the args you need
      // to replace
      for(i = 0; template.args[i] != NULL; i++)
	{
	  if(strcmp(template.args[i], key) == 0)
	    {
	      // Replace key label with actual arg value if found
	      template.args[i] = arg;
	      num_args++;
	      break; // found it
	    }
	}
      // Not entirely sure what I'm supposed to do with this
      template->num_args = num_args;
    }
  // Execute commands in shell
  rc = Shell_run(p, &template);
  apr_pool_destroy(p);
  va_end(argp);
  return rc;

 error:
  if(p) apr_pool_destroy(p);
  return rc;
}

// Run commands in specified shell, pool memory resources in same pool
// as the shell itself
int Shell_run(apr_pool_t *p, Shell *cmd)
{
  apr_procattr_t *attr;
  apr_status_t rv;
  apr_proc_t newproc;

  rv = apr_procattr_create(&attr, p);
  check(rv == APR_SUCCESS, "Failed to creat proc attr.");

  rv = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE);
  check(rv == APR_SUCCESS, "Failed to set IO of command.");

  rv = apr_procattr_dir_set(attr, cmd->dir);
  check(rv == APR_SUCCESS, "Failed to set root to %s", cmd->dir);

  rv = apr_procattr_cmdtype_Set(attr, APR_PROGRAM_PATH);
  check(rv == APR_SUCCESS, "Failed to set command type.");

  // Actually run the command specified in arg list
  rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, attr, p);
  check(rv == APR_SUCCESS, "Failed to run command.");
  
  rv = apr_proc_wait(&newproc, &cmd->exit_code, &cmd->exit_why, APR_WAIT);
  check(rv == APR_CHILD_DONE, "Failed to wait.");

  check(cmd->exit_code == 0, "%s exited badly.", cmd->exe);
  check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crashed.", cmd->exe);
  return 0;

 error:
  return -1;
}

Shell CLEANUP_SH =
  {
    .exe = "rm",
    .dir = "/tmp",
    .args =
    {
      "rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz",
      "/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL
    }
  };

Shell GIT_SH =
  {
    .exe = "git",
    .dir = "/tmp",
    .args =
    {
      "git", "clone", "URL", "pkg-build", NULL
    }
  };

Shell TAR_SH =
  {
    .exe = "tar",
    .dir = "/tmp/pkg-build",
    .args =
    {
      "tar", "-xzf", "FILE", "--strip-components", "1", NULL
    }
  };

Shell CURL_SH =
  {
    .exe = "curl",
    .dir = "/tmp",
    .args =
    {
      "curl", "-L", "-o", "TARGET", "URL", NULL
    }
  };

Shell CONFIGURE_SH =
  {
    .exe = "./configure",
    .dir = "/tmp/pkg-build",
    .args =
    {
      "configure", "OPTS", NULL
    }
  };

Shell MAKE_SH =
  {
    .exe = "make",
    .dir = "/tmp/pkg-build",
    .args =
    {
      "make", "OPTS", NULL
    }
  };

Shell INSTALL_SH =
  {
    .exe = "sudo",
    .dir = "/tmp/pkg-build",
    .args =
    {
      "sudo", "make", "TARGET", NULL
    }
  };

